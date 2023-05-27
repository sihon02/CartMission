#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Stage1GameOverBg.h"
#include "Title.h"
#include "Stage1GameOver.h"
#include "GameOverCursor.h"

#include "TransitionStage1.h"
#include "TransitionStageSelect.h"

#include "StageSelct.h"

#include "Stage1.h"

#include "audio.h"

void Stage1GameOver::Init()
{
	AddGameObject<Stage1GameOverBg>(2);
	AddGameObject<GameOverCursor>(2);

	m_TransitionStage1 = AddGameObject<TransitionStage1>(2);
	m_TransitionStage1->Start(true);

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

void Stage1GameOver::Uninit()
{
	Scene::Uninit();
}

void Stage1GameOver::Update()
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
		m_TransitionStage1->Start(false);
		m_ShotSE1->Play();
	}

	if (Input::GetKeyTrigger(VK_SPACE) && m_Direction == 1)
	{
		m_TransitionStageSelect->Start(false);
		m_ShotSE1->Play();
	}

	if (m_TransitionStage1->GetFinish())
		Manager::SetScene<Stage1>();	//ステージ１にシーン移動

	else if (m_TransitionStageSelect->GetFinish())
		Manager::SetScene<StageSelct>();	//ステージセレクトにシーン移動
}