#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Explanation.h"
#include "ExplanationBg.h"
#include "TitleLogo.h"
#include "Title.h"
#include "TransitionStageSelect.h"

#include "Stage1.h"
#include "Stage2.h"
#include "StageSelct.h"

#include "audio.h"

void Explanation::Init()
{
	AddGameObject<ExplanationBg>(2);
	

	m_TransitionStageSelect = AddGameObject<TransitionStageSelect>(2);
	m_TransitionStageSelect->Start(true);

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\push.wav");

}

void Explanation::Uninit()
{
	Scene::Uninit();
}

void Explanation::Update()
{
	Scene::Update();

	if (Input::GetKeyTrigger(VK_SPACE))
	{
		m_TransitionStageSelect->Start(false);
		m_ShotSE->Play();
	}

	if (m_TransitionStageSelect->GetFinish())
		Manager::SetScene<Title>(); //タイトルにシーン移動
}