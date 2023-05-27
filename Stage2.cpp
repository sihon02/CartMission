#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Stage2.h"
#include "camera.h"
#include "model.h"
#include "Player.h"
#include "BlockEnemy.h"
#include "YokoBlock.h"
#include "Item.h"
#include "Sky.h"
#include "Koura.h"
#include "ItemFrameUi.h"
#include "TitleLogo.h"
#include "ResultUi.h"
#include "Stage2GameoverBg.h"
#include "Explosion.h"
#include "Dokan.h"
#include "TransitionStageSelect.h"
#include "audio.h"
#include "Title.h"
#include "Result.h"
#include "Stage2GameOver.h"
#include "YokoWall.h"
#include "TateBlock.h"
#include "TateBlockObb.h"
#include "TateWall.h"
#include "FailEnemy.h"
#include "GoalBoard.h"
#include "GoalLineStage2.h"
#include "CheckPoint.h"
#include "GoalCountUi.h"
#include "TimeCountUi.h"
#include "GoalUI.h"
#include "Item.h"
#include "ItemUi.h"
#include "StartTime.h"
#include "Stage2Field.h"
#include "CarEnemy.h"
#include "DashBoard.h"
#include "EnemyGoalUi.h"
#include "EnemyCountUi.h"
#include "ChageUi.h"
#include "SpeedMeterUi.h"
#include "MeterUi.h"
#include "ChargeDash.h"
#include "ThunderUi.h"
#include "DashUi.h"

//************ ステージ2 ************//

//ここでゲームオブジェクトを追加したり位置や大きさなど調整できる。

void Stage2::Init()
{
	Koura::Load();

	AddGameObject<Camera>(0);
	AddGameObject<Stage2Field>(1);
	AddGameObject<Player>(1)->SetPosition(D3DXVECTOR3(-40.0f,1.0f,-30.0f));
	AddGameObject<CarEnemy>(1)->SetPosition(D3DXVECTOR3(-25.0f, 1.0f, -30.0f));
	AddGameObject<Sky>(1);
	m_Goalyuka = AddGameObject<GoalLineStage2>(1);

	{
		GoalBoard* goalboard = AddGameObject<GoalBoard>(1);
		goalboard->SetPosition(D3DXVECTOR3(-25.0f, 0.0f, 0.0f));
		goalboard->SetScale(D3DXVECTOR3(7.0f, 3.5f, 10.0f));
	}

	
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(-100.0f, 15.0f, 10.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(-100.0f, 15.0f, 250.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(-100.0f, 15.0f, -250.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(300.0f, 15.0f, 300.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(300.0f, 15.0f, 10.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(300.0f, 15.0f, -250.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(-20.0f, 0.0f, 300.0f));

	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(39.0f, 0.0f, 180.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(92.0f, 0.0f, 180.0f));

	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(39.0f, 0.0f, -180.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(92.0f, 0.0f, -180.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(-100.0f, 0.0f, 400.0f));
	AddGameObject<TateWall>(1)->SetPosition(D3DXVECTOR3(100.0f, 15.0f, 400.0f));
	AddGameObject<TateWall>(1)->SetPosition(D3DXVECTOR3(100.0f, 15.0f, -400.0f));
	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(150.0f, 14.0f, 200.0f));
	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(180.0f, 14.0f, 250.0f));
	AddGameObject<TateBlockObb>(1)->SetPosition(D3DXVECTOR3(100.0f, 1.0f, -350.0f));
	AddGameObject<TateBlockObb>(1)->SetPosition(D3DXVECTOR3(250.0f, 1.0f, -180.0f));


	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(-100.0f, 0.0f, 2.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(120.0f, 0.0f, 70.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(120.0f, 0.0f, 150.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(120.0f, 0.0f, 10.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(120.0f, 0.0f, -70.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(120.0f, 0.0f, -150.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 70.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 150.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 10.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(10.0f, 0.0f, -70.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(10.0f, 0.0f, -150.0f));
 

	AddGameObject<DashBoard>(1)->SetPosition(D3DXVECTOR3(230.0f, 0.0f, 10.0f));

	AddGameObject<Dokan>(1)->SetPosition(D3DXVECTOR3(6.0f, 2.0f, 5.0f));
	AddGameObject<Dokan>(1)->SetPosition(D3DXVECTOR3(50.0f, 2.0f, 20.0f));


	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(200.0f, 3.0f, 0.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(180.0f, 3.0f, 0.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(160.0f, 3.0f, 0.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(250.0f, 3.0f, -100.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(70.0f, 3.0f, -300.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(90.0f, 3.0f, -270.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(200.0f, 3.0f, 0.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(40.0f, 3.0f, -330.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(20.0f, 3.0f, -350.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(180.0f, 3.0f, 50.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(180.0f, 3.0f, 200.0f));
	AddGameObject<Item>(1)->SetPosition(D3DXVECTOR3(180.0f, 3.0f, 230.0f));


	AddGameObject<CheckPoint>(1)->SetPosition(D3DXVECTOR3(230.0f, -1.5f, -30.0f));

	AddGameObject<ThunderUi>(2);
	AddGameObject<ItemFrameUi>(2);
	AddGameObject<GoalCountUi>(2);
	AddGameObject<EnemyCountUi>(2);
	AddGameObject<GoalUi>(2);
	AddGameObject<ItemUi>(2);
	AddGameObject<EnemyGoalUi>(2);
	AddGameObject<StartTime>(2);
	AddGameObject<SpeedMeterUi>(2);
	AddGameObject<MeterUi>(2);
	AddGameObject<ChargeUi>(2);
	AddGameObject<DashUi>(2);




	Audio* bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\Game.wav");
	bgm->Play(true);

	m_TransitionStageSelect = AddGameObject<TransitionStageSelect>(2);
	m_TransitionStageSelect->Start(true);

}

void Stage2::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し

	Koura::Unload();

}

void Stage2::Update()
{
	Scene::Update();//継承元クラスのメソッド呼び出し

	if (m_Goalyuka->GetEnemyGoal())
	{
		Manager::SetScene<Stage2GameOver>();
	}
	else if (m_Goalyuka->GetGoal())
	{
		m_TransitionStageSelect->Start(false);
		Manager::SetScene<Result>();
	}

}