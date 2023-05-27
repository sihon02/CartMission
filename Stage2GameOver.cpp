#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Stage2GameoverBg.h"
#include "Title.h"
#include "Stage2GameOver.h"
#include "GameOverCursor.h"

#include "TransitionStage2.h"
#include "TransitionStageSelect.h"

#include "StageSelct.h"

#include "Stage2.h"

#include "audio.h"


void Stage2GameOver::Init()
{
	AddGameObject<Stage2GameOverBg>(2);
	AddGameObject<GameOverCursor>(2);

	m_TransitionStage2 = AddGameObject<TransitionStage2>(2);
	m_TransitionStage2->Start(true);

	m_TransitionStageSelect = AddGameObject<TransitionStageSelect>(2);
	m_TransitionStageSelect->Start(true);

	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\GameOver.wav");
	bgm->Play(true);

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\cursor.wav");

	m_ShotSE1 = scene->AddGameObject<Audio>(2);
	m_ShotSE1->Load("asset\\audio\\push.wav");

	m_Direction = 0;

}

void Stage2GameOver::Uninit()
{
	Scene::Uninit();
}

void Stage2GameOver::Update()
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
		m_TransitionStage2->Start(false);
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 1)
	{
		m_TransitionStageSelect->Start(false);
		m_ShotSE1->Play();
	}

	if (m_TransitionStage2->GetFinish())
		Manager::SetScene<Stage2>();	//ステージ２にシーン移動

	else if (m_TransitionStageSelect->GetFinish())
		Manager::SetScene<StageSelct>(); //ステージセレクトにシーン移動
}