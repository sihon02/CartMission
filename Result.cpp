#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Result.h"
#include "Title.h"
#include "ResultCursor.h"
#include "ResultUi.h"

#include "Transition.h"
#include "TransitionStageSelect.h"

#include "StageSelct.h"

#include "audio.h"

void Result::Init()
{
	AddGameObject<ResultUi>(2);
	AddGameObject<ResultCursor>(2);

	m_Transition = AddGameObject<Transition>(2);
	m_Transition->Start(true);

	m_TransitionStageSelect = AddGameObject<TransitionStageSelect>(2);
	m_TransitionStageSelect->Start(true);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\GameClear.wav");
	bgm->Play(true);

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\cursor.wav");

	m_ShotSE1 = scene->AddGameObject<Audio>(2);
	m_ShotSE1->Load("asset\\audio\\push.wav");

}

void Result::Uninit()
{
	Scene::Uninit();
}

void Result::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger('D'))
	{
		m_Direction = 1;
		m_ShotSE->Play();
	}

	if (Input::GetKeyTrigger('A'))
	{
		m_Direction = 0;
		m_ShotSE->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 0)
	{
		m_Transition->Start(false);
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 1)
	{
		m_TransitionStageSelect->Start(false);
		m_ShotSE1->Play();
	}

	if (m_Transition->GetFinish())
		Manager::SetScene<StageSelct>();

	else if (m_TransitionStageSelect->GetFinish())
		Manager::SetScene<Title>();
}