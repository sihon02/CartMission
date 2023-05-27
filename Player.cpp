#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "model.h"
#include "Scene.h"
#include "Player.h"
#include "YokoBlock.h"
#include "YokoWall.h"
#include "TateWall.h"
#include "Koura.h"
#include "JumpDai.h"
#include "Enemy.h"
#include "BlockEnemy.h"
#include "FailEnemy.h"
#include "TateBlockObb.h"
#include "TateBlock.h"
#include "CheckPoint.h"
#include "DashBoard.h"
#include "Thunder.h"
#include "ChargeDash.h"   
#include "Dirt.h"
#include "Banana.h"
#include "audio.h"

#include "ItemUi.h"
#include "SpeedMeterUi.h"
#include "ChageUi.h"
#include "DashUi.h"
#include "ThunderUi.h"
#include "Explosion.h"
#include "DashEffect.h"

#define CHARGE_MAX				(100.0f)	

void Player::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\Player.obj");

	m_Position = D3DXVECTOR3(-20.0f, 1.0f, -15.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale	   = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Charge = 0.0f;
	m_ItemType = 0;
	m_JumpUse = 0;
	m_StartTime = 0.0f;
	m_Time = 0;
	m_Tunrderflag = false;
	m_Bnanaflag = false;
	m_StartTimeflag = true;
	m_isClash = false;
	m_isAccele = false;
	m_isThunder = false;
	m_isCheckPoint = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\Charge.wav");
	m_ShotSE2 = scene->AddGameObject<Audio>(2);
	m_ShotSE2->Load("asset\\audio\\dash.wav");
	m_ShotSE3 = scene->AddGameObject<Audio>(2);
	m_ShotSE3->Load("asset\\audio\\Jump.wav");

}


void Player::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Player::Update()
{	
	if (m_StartTimeflag == true) //スタートカウント
	{
		m_StartTime += 0.01f;
	}

	if (m_Charge >= CHARGE_MAX) //チャージの最大溜め
	{
		m_Charge = 100.0f;
	}

	if (m_Rotation.x >= 0.6f)	//プレイヤーのドリフトの角度調整
	{
		m_Rotation.x = 0.5f;
	}

	if (m_Rotation.x <= 0.0f)
	{
		m_Rotation.x = 0.0f;
	}

	if (m_Rotation.z >= 0.6f)
	{
		m_Rotation.z = 0.5f;
	}

	if (m_Rotation.z <= -0.6f)
	{
		m_Rotation.z = -0.6f;
	}


	D3DXVECTOR3 forward = GetForward();
	D3DXVECTOR3 up = GetUp();

	Scene* scene = Manager::GetScene();

	SpeedMeterUi* speedmeter = scene->GetGameObject<SpeedMeterUi>(2);
	ChargeUi* chargeui = scene->GetGameObject<ChargeUi>(2);
	DashUi* dashui = scene->GetGameObject<DashUi>(2);
	ItemUi* itemui = scene->GetGameObject<ItemUi>(2);
	ThunderUi* thunderui = scene->GetGameObject<ThunderUi>(2);
	Thunder* thunder = scene->GetGameObject<Thunder>(1);


	//************** プレイヤー操作 **************//

	if (m_StartTime >= 4.0f)	//スタートカウントを超えたらプレイヤーを操作できる
	{
		m_StartTimeflag = false;	

		if (m_isAccele == false)
		{
			speedmeter->AddSpeedMeter(-1);
		}

		if (m_Charge >= 12.0f && Input::GetKeyRelease('J'))
		{
			dashui->Start(true);
		}

		if (Input::GetKeyPress('A') && m_isClash == false)
		{
			m_Rotation.y -= 0.02f;
			m_Velocity.x -= m_Velocity.x * 0.01f;
		}
		if (Input::GetKeyPress('D') && m_isClash == false)
		{
			m_Rotation.y += 0.02f;
			m_Velocity.x -= m_Velocity.x * 0.01f;
		}

		if (Input::GetKeyPress('L') && m_isClash == false) //アクセル処理
		{
			m_Velocity += forward * 0.02f;
			speedmeter->AddSpeedMeter(1);
			//m_ShotSE->Play();
			m_isAccele = true;
		}

		if (Input::GetKeyRelease('L'))
		{
			m_isAccele = false;
		}

		if (Input::GetKeyPress('K') && m_isClash == false) //ブレーキ処理
		{
			m_Velocity -= forward * 0.02f;
			m_isAccele = true;
			speedmeter->AddSpeedMeter(-1);
		}

		if (Input::GetKeyRelease('K')) //ブレーキ処理
		{
			m_isAccele = false;
		}

		if (Input::GetKeyTrigger('J') && m_JumpUse == 0) //ジャンプ処理
		{
			scene->AddGameObject<ChargeDash>(1)->SetPosition(m_Position);
			m_Velocity += up * 0.1f;
			m_JumpUse = 1;
			m_ShotSE->Play();
  		}

		if (Input::GetKeyRelease('J')) 
		{
			scene->AddGameObject<DashEffect>(1)->SetPosition(m_Position);
			m_Velocity += forward * 0.03f * m_Charge;
			m_Charge = 0.0f;
			chargeui->AddChargeUi(-9);
		}

		//***************** チャージダッシュ ****************//

		if (Input::GetKeyPress('J') && Input::GetKeyPress('D') && m_JumpUse == 0) 
		{
			m_Charge += 1.5f;
			chargeui->AddChargeUi(1);
			m_Velocity -= forward * 0.01f;
		}

		if (Input::GetKeyPress('J') && Input::GetKeyPress('A') && m_JumpUse == 0)
		{
			m_Charge += 1.5f;
			chargeui->AddChargeUi(1);
			m_Velocity -= forward * 0.01f;
		}

		if (m_Tunrderflag == true)
		{
			thunderui->Start(true);
			m_isClash = true;
			m_Velocity = forward * 0.0f;
			m_Rotation.y += 0.03f;
			m_Scale = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
			m_Time += 1;
		}

		if (m_Bnanaflag == true)
		{
			m_isClash = true;
			m_Velocity += forward * 0.01f;
			m_Rotation.y += 0.03f;
			m_Time += 1;
		}

		if (m_Time > 200) //時間を超えたら元に戻す
		{
			m_Tunrderflag = false;
			m_Bnanaflag = false;
			m_isClash = false;
			m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
			m_Time = 0;
		}


		//**************ジャンプ中**************//

		if (Input::GetKeyPress('W') && m_JumpUse == 1)
		{
			m_Velocity -= up * 0.01f;
		}

		if (Input::GetKeyPress('S') && m_JumpUse == 1) 
		{
			speedmeter->AddSpeedMeter(-1);
		}

		if (Input::GetKeyPress('D') && m_JumpUse == 1) 
		{
			speedmeter->AddSpeedMeter(-1);
		}

		if (Input::GetKeyPress('A') && m_JumpUse == 1) 
		{
			speedmeter->AddSpeedMeter(-1);
		}
	}


	//*************** アイテム処理 ***************//

	if (Input::GetKeyTrigger('I') && m_ItemType == 1) //アイテム緑こうら発射処理
	{
		scene->AddGameObject<Koura>(1)->SetPosition(m_Position);
		itemui->SetItemCountUse(0);
		m_ItemType = 0;
		m_ShotSE->Play();
	}
	if (Input::GetKeyTrigger('I') && m_ItemType == 2) //アイテムキノコダッシュ処理
	{
		itemui->SetItemCountUse(0);
		dashui->Start(true);
		scene->AddGameObject<DashEffect>(1)->SetPosition(m_Position);
		m_Velocity += forward * 2.0f;
		m_ItemType = 0;
		m_ShotSE2->Play();
	}
	if (Input::GetKeyTrigger('I') && m_ItemType == 3) //アイテムダブルキノコダッシュ処理
	{
		itemui->SetItemCountUse(2);
		dashui->Start(true);
		scene->AddGameObject<DashEffect>(1)->SetPosition(m_Position);
		m_Velocity += forward * 2.0f;
		m_ItemType = 2;
		m_ShotSE2->Play();
	}
	if (Input::GetKeyTrigger('I') && m_ItemType == 4) //アイテムトリプルキノコダッシュ処理
	{
		itemui->SetItemCountUse(3);
		dashui->Start(true);
		scene->AddGameObject<DashEffect>(1)->SetPosition(m_Position);
		m_Velocity += forward * 2.0f;
		m_ItemType = 3;
		m_ShotSE2->Play();
	}
	
	//重力
	m_Velocity.y -= 0.005f;

	//抵抗
	m_Velocity.x -= m_Velocity.x * 0.02f;
	m_Velocity.y -= m_Velocity.y * 0.03f;
	m_Velocity.z -= m_Velocity.z * 0.02f;


	D3DXVECTOR3 oldPosition = m_Position; 

	//移動
	m_Position += m_Velocity;
	

	float groundHeight = 1.0f;


	std::vector<YokoBlock*> yokoList = scene->GetGameObjects<YokoBlock>(1);
	std::vector<YokoWall*> yokowallList = scene->GetGameObjects<YokoWall>(1);
	std::vector<TateWall*> tatewallList = scene->GetGameObjects<TateWall>(1);
	std::vector<TateBlockObb*> tateblockobbList = scene->GetGameObjects<TateBlockObb>(1);
	std::vector<TateBlock*> tateblockList = scene->GetGameObjects<TateBlock>(1);
	std::vector<Jumpdai*> jumpdaiList = scene->GetGameObjects<Jumpdai>(1);
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1);
	std::vector<BlockEnemy*> blockenemyList = scene->GetGameObjects<BlockEnemy>(1);
	std::vector<FailEnemy*> failenemyList = scene->GetGameObjects<FailEnemy>(1);
	std::vector<DashBoard*> dashboardList = scene->GetGameObjects<DashBoard>(1);
	std::vector<Dirt*> dirtList = scene->GetGameObjects<Dirt>(1);
	std::vector<CheckPoint*> checkpointList = scene->GetGameObjects<CheckPoint>(1);
	std::vector<Banana*> bananaList = scene->GetGameObjects<Banana>(1);



	//******************* 当たり判定 ******************//


	for (YokoBlock* yokoform : yokoList) //横ブロックの当たり判定
	{
		D3DXVECTOR3 yokoformPosition = yokoform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 yokoformScale = yokoform->GetScale();		//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = yokoformPosition.x + (yokoformScale.x / 2);
		float Bxmin = yokoformPosition.x - (yokoformScale.x / 2);
		float Bymax = yokoformPosition.y + (yokoformScale.y / 2);
		float Bymin = yokoformPosition.y - (yokoformScale.y / 2);
		float Bzmax = yokoformPosition.z + (yokoformScale.z / 2);
		float Bzmin = yokoformPosition.z - (yokoformScale.z / 2);

		if ((Axmax + 27.0f > Bxmin) && (Axmin < Bxmax + 27.0f))
		{
			if ((Aymin < Bymax + 2.0f) && (Aymax + 2.0f > Bymin))
			{
				if ((Azmax + 3.0f > Bzmin ) && (Azmin < Bzmax + 3.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}
			}

		}
	}

	for (YokoWall* yokowallform : yokowallList) //壁の当たり判定
	{
		D3DXVECTOR3 yokowallformPosition = yokowallform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 yokowallformScale = yokowallform->GetScale();		//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = yokowallformPosition.x + (yokowallformScale.x / 2);
		float Bxmin = yokowallformPosition.x - (yokowallformScale.x / 2);
		float Bymax = yokowallformPosition.y + (yokowallformScale.y / 2);
		float Bymin = yokowallformPosition.y - (yokowallformScale.y / 2);
		float Bzmax = yokowallformPosition.z + (yokowallformScale.z / 2);
		float Bzmin = yokowallformPosition.z - (yokowallformScale.z / 2);

		if ((Axmax + 3.5f > Bxmin) && (Axmin < Bxmax + 3.5f))
		{
			if ((Aymin < Bymax + 70.0f) && (Aymax + 70.0f > Bymin))
			{

					m_Position.x = oldPosition.x;
					m_Position.y = oldPosition.y;
					m_Position.z = oldPosition.z;
					m_Velocity = forward * 0.0f;
					speedmeter->AddSpeedMeter(-5);
			}
		}
	}


	for (TateBlock* tateblockform : tateblockList) //縦ブロックの当たり判定
	{
		D3DXVECTOR3 tateblockformPosition = tateblockform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 tateblockformScale = tateblockform->GetScale();			//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = tateblockformPosition.x + (tateblockformScale.x / 2);
		float Bxmin = tateblockformPosition.x - (tateblockformScale.x / 2);
		float Bymax = tateblockformPosition.y + (tateblockformScale.y / 2);
		float Bymin = tateblockformPosition.y - (tateblockformScale.y / 2);
		float Bzmax = tateblockformPosition.z + (tateblockformScale.z / 2);
		float Bzmin = tateblockformPosition.z - (tateblockformScale.z / 2);

		if ((Axmax + 2.8f > Bxmin) && (Axmin < Bxmax + 2.8f))
		{
			if ((Aymin < Bymax + 1.0f) && (Aymax + 1.0f > Bymin))
			{
				if ((Azmax + 40.0f > Bzmin) && (Azmin < Bzmax + 40.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.y = oldPosition.y;
					m_Position.z = oldPosition.z;
					m_Velocity = forward * 0.0f;
					speedmeter->AddSpeedMeter(-5);
				}
			}
		}
	}

	for (TateWall* tatewallform : tatewallList) //壁の当たり判定
	{
		D3DXVECTOR3 tatewallformPosition = tatewallform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 tatewallformScale = tatewallform->GetScale();		//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = tatewallformPosition.x + (tatewallformScale.x / 2);
		float Bxmin = tatewallformPosition.x - (tatewallformScale.x / 2);
		float Bymax = tatewallformPosition.y + (tatewallformScale.y / 2);
		float Bymin = tatewallformPosition.y - (tatewallformScale.y / 2);
		float Bzmax = tatewallformPosition.z + (tatewallformScale.z / 2);
		float Bzmin = tatewallformPosition.z - (tatewallformScale.z / 2);

		if ((Axmax + 200.0f > Bxmin) && (Axmin < Bxmax + 200.0f))
		{
			if ((Aymin < Bymax + 70.0f) && (Aymax + 70.0f > Bymin))
			{
				if ((Azmax + 1.0f > Bzmin) && (Azmin < Bzmax + 1.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
					speedmeter->AddSpeedMeter(-5);
				}
			}
		}
	}

	for (TateBlockObb* tateblockobbform : tateblockobbList) //縦ブロックObbバージョンの当たり判定
	{
		D3DXVECTOR3 tateblockobbformPosition = tateblockobbform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 tateblockobbformScale = tateblockobbform->GetScale();		//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = tateblockobbformPosition.x + (tateblockobbformScale.x / 2);
		float Bxmin = tateblockobbformPosition.x - (tateblockobbformScale.x / 2);
		float Bymax = tateblockobbformPosition.y + (tateblockobbformScale.y / 2);
		float Bymin = tateblockobbformPosition.y - (tateblockobbformScale.y / 2);
		float Bzmax = tateblockobbformPosition.z + (tateblockobbformScale.z / 2);
		float Bzmin = tateblockobbformPosition.z - (tateblockobbformScale.z / 2);


		D3DXVECTOR3 direction = m_Position - tateblockobbformPosition;
		D3DXVECTOR3 obbx, obbz;
		float obbLenx, obbLenz;
		obbx = tateblockobbform->GetObbX();
		obbLenx = D3DXVec3Length(&obbx);
		obbx /= obbLenx;
		obbz = tateblockobbform->GetObbZ();
		obbLenz = D3DXVec3Length(&obbz);
		obbz /= obbLenz;
		float lenX, lenZ;
		lenX = D3DXVec3Dot(&obbx, &direction);
		lenZ = D3DXVec3Dot(&obbz, &direction);
		if (fabs(lenX) < obbLenx && fabs(lenZ) < obbLenz)
		{
			m_Position.x = oldPosition.x;
			m_Position.y = oldPosition.y;
			m_Position.z = oldPosition.z;
			m_Velocity = forward * 0.0f;
		}
	}

	for (Jumpdai* jumpdaiform : jumpdaiList) //ジャンプ台の当たり判定
	{
		D3DXVECTOR3 jumpdaiformPosition = jumpdaiform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 jumpdaiformScale = jumpdaiform->GetScale();			//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = jumpdaiformPosition.x + (jumpdaiformScale.x / 2);
		float Bxmin = jumpdaiformPosition.x - (jumpdaiformScale.x / 2);
		float Bymax = jumpdaiformPosition.y + (jumpdaiformScale.y / 2);
		float Bymin = jumpdaiformPosition.y - (jumpdaiformScale.y / 2);
		float Bzmax = jumpdaiformPosition.z + (jumpdaiformScale.z / 2);
		float Bzmin = jumpdaiformPosition.z - (jumpdaiformScale.z / 2);

		if ((Axmax + 7.0f > Bxmin) && (Axmin < Bxmax + 7.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 7.0f > Bzmin) && (Azmin < Bzmax + 7.0f))
				{
					m_Velocity.y = 0.3f;
					m_ShotSE3->Play();
				}
			}

		}
	}

	for (Enemy* enemyform : enemyList) //敵の当たり判定
	{
		D3DXVECTOR3 enemyformPosition = enemyform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 enemyformScale = enemyform->GetScale();			//サイズを受け取る

		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = enemyformPosition.x + (enemyformScale.x / 2);
		float Bxmin = enemyformPosition.x - (enemyformScale.x / 2);
		float Bymax = enemyformPosition.y + (enemyformScale.y / 2);
		float Bymin = enemyformPosition.y - (enemyformScale.y / 2);
		float Bzmax = enemyformPosition.z + (enemyformScale.z / 2);
		float Bzmin = enemyformPosition.z - (enemyformScale.z / 2);


		if ((Axmax + 6.0f > Bxmin) && (Axmin < Bxmax + 6.0f))
		{
			if ((Aymin < Bymax + 5.0f) && (Aymax + 5.0f > Bymin))
			{
				if ((Azmax + 7.0f > Bzmin) && (Azmin < Bzmax + 7.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
					m_Velocity = forward * 0.0f;
				}
			}
		}
	}

	for (BlockEnemy* blockenemyform : blockenemyList) //ブロック型の敵の当たり判定
	{
		D3DXVECTOR3 blockenemyformPosition = blockenemyform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 blockenemyformScale = blockenemyform->GetScale();		//サイズを受け取る

		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = blockenemyformPosition.x + (blockenemyformScale.x / 2);
		float Bxmin = blockenemyformPosition.x - (blockenemyformScale.x / 2);
		float Bymax = blockenemyformPosition.y + (blockenemyformScale.y / 2);
		float Bymin = blockenemyformPosition.y - (blockenemyformScale.y / 2);
		float Bzmax = blockenemyformPosition.z + (blockenemyformScale.z / 2);
		float Bzmin = blockenemyformPosition.z - (blockenemyformScale.z / 2);

		if ((Axmax + 6.0f > Bxmin) && (Axmin < Bxmax + 6.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 7.0f > Bzmin) && (Azmin < Bzmax + 7.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}
			}
		}
	}

	for (FailEnemy* failenemyform : failenemyList) //落下型の敵の当たり判定
	{
		D3DXVECTOR3 failenemyformPosition = failenemyform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 failenemyformScale = failenemyform->GetScale();			//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = failenemyformPosition.x + (failenemyformScale.x / 2);
		float Bxmin = failenemyformPosition.x - (failenemyformScale.x / 2);
		float Bymax = failenemyformPosition.y + (failenemyformScale.y / 2);
		float Bymin = failenemyformPosition.y - (failenemyformScale.y / 2);
		float Bzmax = failenemyformPosition.z + (failenemyformScale.z / 2);
		float Bzmin = failenemyformPosition.z - (failenemyformScale.z / 2);

		if ((Axmax + 6.0f > Bxmin) && (Axmin < Bxmax + 6.0f))
		{
			if ((Aymin < Bymax + 5.0f) && (Aymax + 5.0f > Bymin))
			{
				if ((Azmax + 8.0f > Bzmin) && (Azmin < Bzmax + 8.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
					m_Velocity = forward * 0.0f;
				}
			}

		}
	}

	for (DashBoard* dashboardform : dashboardList) //ダッシュボードの当たり判定
	{
		D3DXVECTOR3 dashboardformPosition = dashboardform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 dashboardformScale = dashboardform->GetScale();			//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = dashboardformPosition.x + (dashboardformScale.x / 2);
		float Bxmin = dashboardformPosition.x - (dashboardformScale.x / 2);
		float Bymax = dashboardformPosition.y + (dashboardformScale.y / 2);
		float Bymin = dashboardformPosition.y - (dashboardformScale.y / 2);
		float Bzmax = dashboardformPosition.z + (dashboardformScale.z / 2);
		float Bzmin = dashboardformPosition.z - (dashboardformScale.z / 2);

		if ((Axmax + 5.0f > Bxmin) && (Axmin < Bxmax + 5.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 2.0f > Bzmin) && (Azmin < Bzmax + 2.0f))
				{
					m_Velocity += forward * 0.5f;
					m_ShotSE2->Play();
					dashui->Start(true);
				}
			}
		}
	}

	for (Dirt* dirtform : dirtList) //泥の当たり判定
	{
		D3DXVECTOR3 dirtformPosition = dirtform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 dirtformScale = dirtform->GetScale();		//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = dirtformPosition.x + (dirtformScale.x / 2);
		float Bxmin = dirtformPosition.x - (dirtformScale.x / 2);
		float Bymax = dirtformPosition.y + (dirtformScale.y / 2);
		float Bymin = dirtformPosition.y - (dirtformScale.y / 2);
		float Bzmax = dirtformPosition.z + (dirtformScale.z / 2);
		float Bzmin = dirtformPosition.z - (dirtformScale.z / 2);

		if ((Axmax + 12.0f > Bxmin) && (Axmin < Bxmax + 12.0f))
		{
			if ((Aymin  < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 12.0f > Bzmin) && (Azmin < Bzmax + 12.0f))
				{
					if (Input::GetKeyPress('L')) //アクセル
					{
						m_Velocity = forward * 0.07f;
					}

					if (Input::GetKeyPress('K')) //バック
					{
						m_Velocity += forward * 0.019f;
					}

					m_Position.y = 0.8f;//プレイヤーを少し埋もれさせる
				}
			}
		}

	}

	for (CheckPoint* checkpointform : checkpointList) //チェックポイントの当たり判定
	{
		D3DXVECTOR3 checkpointformPosition = checkpointform->GetPosition();	//座標を受け取る
		D3DXVECTOR3 checkpointformScale = checkpointform->GetScale();		//サイズを受け取る


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = checkpointformPosition.x + (checkpointformScale.x / 2);
		float Bxmin = checkpointformPosition.x - (checkpointformScale.x / 2);
		float Bymax = checkpointformPosition.y + (checkpointformScale.y / 2);
		float Bymin = checkpointformPosition.y - (checkpointformScale.y / 2);
		float Bzmax = checkpointformPosition.z + (checkpointformScale.z / 2);
		float Bzmin = checkpointformPosition.z - (checkpointformScale.z / 2);

		if ((Axmax + 100.0f > Bxmin) && (Axmin < Bxmax + 70.0f))
		{
			if ((Aymin < Bymax + 2.0f) && (Aymax + 2.0f > Bymin))
			{
				if ((Azmax + 7.0f > Bzmin) && (Azmin < Bzmax + 7.0f))
				{
					m_isCheckPoint = true;
				}
			}

		}
	}


	for (Banana* banana : bananaList)  //アイテムの当たり判定
	{
		D3DXVECTOR3 bananaPosition = banana->GetPosition();

		D3DXVECTOR3 direction = m_Position - bananaPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 5.0f)
		{
			m_Bnanaflag = true;
		}
	}

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
		m_Rotation.z = 0.0f;
		m_JumpUse = 0;
		m_Rotation.x = 0.0f;
	}


}


void Player::Draw()
{
	//入力レイアウト設定
	Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

	//シェーダー設定
	Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	//マトリックス設定
	D3DXMATRIX world, scale, rot, trans;
	D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
	D3DXMatrixTranslation(&trans, m_Position.x, m_Position.y, m_Position.z);
	world = scale * rot * trans;
	Renderer::SetWorldMatrix(&world);

	m_Model->Draw();

}
