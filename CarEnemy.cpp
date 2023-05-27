#include "main.h"
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "model.h"
#include "Scene.h"
#include "CarEnemy.h"
#include "YokoBlock.h"
#include "YokoWall.h"
#include "Thunder.h"
#include "Player.h"
#include "JumpDai.h"
#include "Enemy.h"
#include "Item.h"
#include "CheckPoint.h"

#include "ThunderUi.h"

#include "audio.h"


void CarEnemy::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\EnemyCart.obj");


	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	//m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ItemUse = 0;
	m_Direction = 0;
	m_Time = 0;
	m_UseTime = 0.0f;
	m_UseTimeflag = true;
	m_RedKouraflag = false;
	m_isCheckPointEnemy = false;
	m_isTunrderEnemyflag = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\thunder.wav");

}


void CarEnemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void CarEnemy::Update()
{
	if (m_UseTimeflag == true)
	{
		m_UseTime += 0.01f;
	}

	D3DXVECTOR3 forward = GetForward();
	Scene* scene = Manager::GetScene();
	ThunderUi* thunderui = scene->GetGameObject<ThunderUi>(2);
	Player* player = scene->GetGameObject<Player>(1);
    m_PlayerPosition = player->GetPosition();
	State();

	m_State = WAIT;

	//*********敵(カート)処理********//

	if (m_UseTime >= 4.0f)
	{
		m_State = MOVE;

		if (m_ItemUse == 3) //アイテムサンダー
		{
			m_State = ATTACK;
		}
	}




	//重力
	m_Velocity.y -= 0.01f;

	//抵抗
	m_Velocity.x -= m_Velocity.x * 0.4f;
	m_Velocity.y -= m_Velocity.y * 0.01f;
	m_Velocity.z -= m_Velocity.z * 0.4f;

	D3DXVECTOR3 oldPosition = m_Position;

	//移動
	m_Position += m_Velocity;

	float groundHeight = 1.0f;

	std::vector<YokoBlock*> yokoList = scene->GetGameObjects<YokoBlock>(1);
	std::vector<YokoWall*> yokowallList = scene->GetGameObjects<YokoWall>(1);
	std::vector<Jumpdai*> jumpdaiList = scene->GetGameObjects<Jumpdai>(1);
	std::vector<Enemy*> enemyList = scene->GetGameObjects<Enemy>(1);
	std::vector<CheckPoint*> checkpointList = scene->GetGameObjects<CheckPoint>(1);

	for (YokoBlock* yokoform : yokoList) //横ブロックの当たり判定
	{
		D3DXVECTOR3 yokoformPosition = yokoform->GetPosition(); //座標を受け取る
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
				if ((Azmax + 3.0f > Bzmin) && (Azmin < Bzmax + 3.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}
			}

		}
	}


	for (YokoWall* yokowallform : yokowallList) //岩の当たり判定
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

		if ((Axmax + 15.0f > Bxmin) && (Axmin < Bxmax + 15.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 2.0f > Bzmin) && (Azmin < Bzmax + 2.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}
			}

		}
	}

	

	for (Enemy* enemyform : enemyList) //岩の当たり判定
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

		if ((Axmax + 2.0f > Bxmin) && (Axmin < Bxmax + 2.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 5.0f > Bzmin) && (Azmin < Bzmax + 5.0f))
				{
					m_Position.x = oldPosition.x;
					m_Position.z = oldPosition.z;
				}
			}
		}
	}


	for (CheckPoint* checkpointform : checkpointList) //ジャンプ台の当たり判定
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

		if ((Axmax + 100.0f > Bxmin) && (Axmin < Bxmax + 100.0f))
		{
			if ((Aymin < Bymax + 2.0f ) && (Aymax + 2.0f > Bymin))
			{
				if ((Azmax + 7.0f > Bzmin) && (Azmin < Bzmax + 7.0f))
				{
					m_isCheckPointEnemy = true;
				}
			}

		}
	}

	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
		m_Velocity.y = 0.0f;
	}

}


void CarEnemy::Draw()
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

void CarEnemy::State()
{
	switch (m_State)
	{
	case WAIT:
		Wait();
		break;
	case MOVE:
		Move();
		break;
	case ATTACK:
		Attack();
		break;
	}
}

void CarEnemy::Wait()
{
	D3DXVECTOR3 forward = GetForward();

	m_Velocity = forward * 0.0f;
}

void CarEnemy::Move()
{
	D3DXVECTOR3 forward = GetForward();
	D3DXVECTOR3 up = GetUp();

	m_UseTimeflag = false;

	if (m_RedKouraflag == false)
	{
		m_Velocity += forward * 0.6f;
	}

	if (m_RedKouraflag == true)
	{
		m_Velocity += up * 0.01f;
		m_Time += 1;
	}

	if (m_Time > 200)
	{
		m_RedKouraflag = false;
		m_Time = 0;
	}


	if (m_Position.z >= 200.0f && m_Direction == 0)
	{
		m_Rotation.y = D3DX_PI * 0.5f;
		m_Direction = 1;
	}

	if (m_Position.x >= 200.0f && m_Direction == 1)
	{
		m_Rotation.y += D3DX_PI * 0.5f;
		m_Direction = 2;
	}

	if (m_Position.z <= -220.0f && m_Direction == 2)
	{
		m_Rotation.y -= D3DX_PI * 1.5f;
		m_Direction = 3;
	}

	if (m_Position.x <= -30.0f && m_Direction == 3)
	{
		m_Rotation.y = D3DX_PI * 0.0f;
		m_Direction = 0;
	}


}



void CarEnemy::Attack()
{
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(1);
	m_PlayerPosition = player->GetPosition();

	scene->AddGameObject<Thunder>(1)->SetPosition(m_PlayerPosition);
	player->IsThunder(true);
	m_ItemUse = 0;
	m_ShotSE->Play();
}
