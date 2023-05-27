#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Title.h"
#include "TitleLogo.h"
#include "TitleFrame.h"
#include "TransitionStageSelect.h"
#include "Transition.h"

#include "Explanation.h"
#include "StageSelct.h"

#include "audio.h"

void Title::Init()
{
	AddGameObject<Titlelogo>(2);
	AddGameObject<TitleCursor>(2);

	m_TransitionStageSelect = AddGameObject<TransitionStageSelect>(2);
	m_TransitionStageSelect->Start(true);

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

void Title::Uninit()
{
	Scene::Uninit();
}

void Title::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger('W') && m_Direction > 0)
	{
		m_Direction -= 1;
		m_ShotSE->Play();
	}

	if (Input::GetKeyTrigger('S') && m_Direction < 2)
	{
		m_Direction += 1;
		m_ShotSE->Play();
	}


	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 0)
	{
		m_TransitionStageSelect->Start(false);
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 1)
	{
		m_Transition->Start(false);
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 2)
	{
		exit(0);
	}

	if (m_TransitionStageSelect->GetFinish())
		Manager::SetScene<StageSelct>(); //ステージセレクトのシーン移動

	else if (m_Transition->GetFinish())
		Manager::SetScene<Explanation>();	//操作説明のシーン移動

}