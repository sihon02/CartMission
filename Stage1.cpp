#include <stdlib.h>
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"

#include "Stage1.h"
#include "camera.h"

#include "model.h"
#include "Player.h"
#include "Enemy.h"
#include "YokoBlock.h"
#include "TateBlock.h"
#include "ItemStage1.h"
#include "Sky.h"
#include "Koura.h"
#include "Banana.h"
#include "ItemFrameUi.h"
#include "TitleLogo.h"
#include "ResultUi.h"
#include "Explosion.h"
#include "ChageUi.h"
#include "Dokan.h"
#include "Transition.h"
#include "audio.h"
#include "Title.h"
#include "Result.h"
#include "Stage1GameOver.h"
#include "Stage1Field.h"
#include "YokoWall.h"
#include "TateWall.h" 
#include "FailEnemy.h"
#include "GoalBoard.h"
#include "GoalLineStage1.h"
#include "JumpDai.h"
#include "GoalCountUi.h"
#include "TimeCountUi.h"
#include "GoalUI.h"
#include "StartTime.h"
#include "DashBoard.h"
#include "ItemUi.h"
#include "TimeUi.h"
#include "SpeedMeterUi.h"
#include "MeterUi.h"
#include "TateBlockObb.h"
#include "Dirt.h"
#include "CheckPoint.h"
#include "DashUi.h"

//********** ステージ１ ************//

//ここでゲームオブジェクトを追加したり位置や大きさなど調整できる。

void Stage1::Init()
{
	Koura::Load();

	AddGameObject<Camera>(0);
	AddGameObject<Stage1Field>(1);

	AddGameObject<Player>(1);
	AddGameObject<Sky>(1);
	m_Goalyuka = AddGameObject<GoalLineStage1>(1);
	AddGameObject<GoalBoard>(1)->SetPosition(D3DXVECTOR3(-18.0f, 1.0f, 0.0f));

	AddGameObject<DashBoard>(1)->SetPosition(D3DXVECTOR3(0.0f, 0.1f, 100.0f));
	AddGameObject<DashBoard>(1)->SetPosition(D3DXVECTOR3(230.0f, 0.1f, 0.0f));
	AddGameObject<DashBoard>(1)->SetPosition(D3DXVECTOR3(-30.0f, 0.1f, -130.0f));
	AddGameObject<Dirt>(1)->SetPosition(D3DXVECTOR3(210.0f, 0.0f, 100.0f));
	AddGameObject<Dirt>(1)->SetPosition(D3DXVECTOR3(240.0f, 0.0f, 92.0f));

	AddGameObject<Banana>(1)->SetPosition(D3DXVECTOR3(250.0f, 0.0f, -200.0f));
	AddGameObject<Banana>(1)->SetPosition(D3DXVECTOR3(220.0f, 0.0f, -120.0f));
	AddGameObject<Banana>(1)->SetPosition(D3DXVECTOR3(190.0f, 0.0f, -150.0f));
	AddGameObject<Banana>(1)->SetPosition(D3DXVECTOR3(240.0f, 0.0f, 0.0f));
	AddGameObject<Banana>(1)->SetPosition(D3DXVECTOR3(245.0f, 0.0f, 30.0f));
	AddGameObject<Banana>(1)->SetPosition(D3DXVECTOR3(195.0f, 0.0f,-170.0f));

	AddGameObject<Dokan>(1)->SetPosition(D3DXVECTOR3(6.0f, 2.0f, 5.0f));
	AddGameObject<Dokan>(1)->SetPosition(D3DXVECTOR3(200.0f, 2.0f, 5.0f));
	AddGameObject<Dokan>(1)->SetPosition(D3DXVECTOR3(60.0f, 2.0f, -50.0f));

	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(-100.0f, 15.0f, 10.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(-100.0f, 15.0f, 250.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(-100.0f, 15.0f, -250.0f));
	AddGameObject<TateWall>(1)->SetPosition(D3DXVECTOR3(100.0f, 15.0f, 400.0f));
	AddGameObject<TateWall>(1)->SetPosition(D3DXVECTOR3(100.0f, 15.0f, -400.0f));
	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(150.0f, 20.0f, 300.0f));
	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(150.0f, 20.0f, 250.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(300.0f, 15.0f, 300.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(300.0f, 15.0f, 10.0f));
	AddGameObject<YokoWall>(1)->SetPosition(D3DXVECTOR3(300.0f, 15.0f, -250.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(55.0f, 0.0f, 230.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(105.0f, 0.0f, 230.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(155.0f, 0.0f, 230.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(55.0f,  0.0f,-230.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(105.0f, 0.0f,-230.0f));
	AddGameObject<YokoBlock>(1)->SetPosition(D3DXVECTOR3(155.0f, 0.0f,-230.0f));

	AddGameObject<TateBlockObb>(1)->SetPosition(D3DXVECTOR3(150.0f, 0.0f, -340.0f));
	AddGameObject<TateBlockObb>(1)->SetPosition(D3DXVECTOR3(100.0f, 0.0f, -255.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(180.0f, 0.0f, -35.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(180.0f, 0.0f, -115.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(180.0f, 0.0f, -190.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(180.0f, 0.0f,  45.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(180.0f, 0.0f,  120.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(180.0f, 0.0f,  198.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(270.0f, 0.0f, 110.0f));

	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -35.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -115.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, -190.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, 45.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, 120.0f));
	AddGameObject<TateBlock>(1)->SetPosition(D3DXVECTOR3(30.0f, 0.0f, 198.0f));
	
	

	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(10.0f, 2.0f, -300.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(10.0f, 2.0f,  300.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(200.0f, 2.0f, 300.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(250.0f, 2.0f, 350.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(-50.0f, 2.0f, -300.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(-50.0f, 2.0f, -100.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(200.0f, 2.0f, -200.0f));
	AddGameObject<ItemStage1>(1)->SetPosition(D3DXVECTOR3(230.0f, 2.0f, -200.0f));


	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(100.0f, 20.0f, 300.0f));
	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(80.0f, 20.0f,  300.0f));
	AddGameObject<FailEnemy>(1)->SetPosition(D3DXVECTOR3(70.0f, 20.0f,  350.0f));

	AddGameObject<Jumpdai>(1)->SetPosition(D3DXVECTOR3(210.0f, 0.0f, 130.0f));
	AddGameObject<CheckPoint>(1)->SetPosition(D3DXVECTOR3(230.0f, -1.5f, -30.0f));


	AddGameObject<DashUi>(2);
	AddGameObject<ItemFrameUi>(2);
	AddGameObject<GoalCountUi>(2);

	AddGameObject<GoalUi>(2);
	AddGameObject<StartTime>(2);
	AddGameObject<ItemUi>(2);
	AddGameObject<ChargeUi>(2);
	AddGameObject<TimeUi>(2);
	AddGameObject<SpeedMeterUi>(2);
	AddGameObject<MeterUi>(2);
	m_TimeCount = AddGameObject<TimeCountUi>(2);

	Audio *bgm = AddGameObject<Audio>(2);
	bgm->Load("asset\\audio\\Game2.wav");
	bgm->Play(true);

	AddGameObject<Transition>(2)->Start(true);
	m_Transition = AddGameObject<Transition>(2);
	m_Transition->Start(true);
}

void Stage1::Uninit()
{
	Scene::Uninit();//継承元クラスのメソッド呼び出し

	Koura::Unload();

}

void Stage1::Update()
{
	Scene::Update();//継承元クラスのメソッド呼び出し

	if (m_Goalyuka->GetGoal())
	{
		Manager::SetScene<Result>();
	}
	else if (m_TimeCount->GetTimeflag())
	{
		Manager::SetScene<Stage1GameOver>();
	}

}
