#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "StageSelct.h"
#include "StageSelctbg.h"
#include "SelectCursor.h"
#include "SelectUi.h"
#include "SelectUi2.h"
#include "TransitionStage1.h"
#include "TransitionStage2.h" 
#include "Transition.h"

#include "Stage1.h"
#include "Stage2.h"
#include "Title.h"

#include "audio.h"

void StageSelct::Init()
{
	AddGameObject<StageSelctBg>(2);
	AddGameObject<SelectCursor>(2);
	AddGameObject<SelctUi>(2);
	AddGameObject<SelctUi2>(2);

	m_TransitionStage1 = AddGameObject<TransitionStage1>(2);
	m_TransitionStage1->Start(true);

	m_TransitionStage2 = AddGameObject<TransitionStage2>(2);
	m_TransitionStage2->Start(true);

	m_Transition = AddGameObject<Transition>(2);
	m_Transition->Start(true);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\Title.wav");
	bgm->Play(true);

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\cursor.wav");

	m_ShotSE1 = scene->AddGameObject<Audio>(2);
	m_ShotSE1->Load("asset\\audio\\push.wav");

	m_Direction = 0;
}

void StageSelct::Uninit()
{
	Scene::Uninit();
}

void StageSelct::Update()
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

	if (Input::GetKeyTrigger('W'))
	{
		m_Direction = 2;
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger('S'))
	{
		m_Direction = 0;
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 0)
	{
		m_TransitionStage1->Start(false);
		m_ShotSE1->Play();
	}

	if(Input::GetKeyTrigger(VK_SPACE) && m_Direction == 1)
	{
		m_TransitionStage2->Start(false);
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 2)
	{
		m_Transition->Start(false);
		m_ShotSE1->Play();
	}

	if (m_TransitionStage1->GetFinish())
	{
		Manager::SetScene<Stage1>();
	}
	
	else if (m_TransitionStage2->GetFinish())
	{
		Manager::SetScene<Stage2>();
	}

	else if (m_Transition->GetFinish())
	{
		Manager::SetScene<Title>();
	}

}