#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"
#include "model.h"
#include "Koura.h"
#include "enemy.h"
#include "CarEnemy.h"
#include "Explosion.h"
#include "YokoWall.h"
#include "YokoBlock.h"
#include "TateBlock.h"
#include "TateBlockObb.h"
#include "Player.h"
#include "input.h"

Model* Koura::m_Model;//スタティックメンバ変数はcppで再度宣言

void Koura::Load()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\koura.obj");
}

void Koura::Unload()
{
	m_Model->Unload();
	delete m_Model;
}

void Koura::Init()
{
	//VERTEX_3D vertex[4];

	m_Position = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");
	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}


void Koura::Uninit()
{
	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Koura::Update()
{

	Scene* scene = Manager::GetScene();

	D3DXVECTOR3 forward = GetForward();
	D3DXVECTOR3 right = GetRight();

	Player* player = scene->GetGameObject<Player>(1);
	m_PlayerPosition = player->GetForward();


	m_Position += m_PlayerPosition * 1.0f;
	

	std::vector<Enemy*> enemyList= scene->GetGameObjects<Enemy>(1);
	std::vector<YokoWall*> yokowallList = scene->GetGameObjects<YokoWall>(1);
	std::vector<YokoBlock*> yokoList = scene->GetGameObjects<YokoBlock>(1);
	std::vector<CarEnemy*> carenemyList = scene->GetGameObjects<CarEnemy>(1);
	std::vector<TateBlock*> tateblockList = scene->GetGameObjects<TateBlock>(1);
	std::vector<TateBlockObb*> tateblockobbList = scene->GetGameObjects<TateBlockObb>(1);

	for (Enemy* enemy : enemyList)
	{
		D3DXVECTOR3 enemyPosition = enemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - enemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 2.0f)
		{
			scene->AddGameObject<Explosion>(1)->SetPosition(enemyPosition);
			enemy->SetDestroy();
			SetDestroy();	
			return;
		}
	}


	for (CarEnemy* carenemy : carenemyList)  //アイテムの当たり判定
	{
		D3DXVECTOR3 carenemyPosition = carenemy->GetPosition();

		D3DXVECTOR3 direction = m_Position - carenemyPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 6.0f)
		{
			//m_ShotSE->Play();
			scene->AddGameObject<Explosion>(1)->SetPosition(carenemyPosition);
			carenemy->IsRedKoura(true);
			SetDestroy();	//当たったら消える
			return;
		}
	}

	for (YokoWall* yokowallform : yokowallList) //岩の当たり判定
	{
		D3DXVECTOR3 yokowallformPosition = yokowallform->GetPosition();
		D3DXVECTOR3 yokowallformScale = yokowallform->GetScale();


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

		if ((Axmax + 12.0f > Bxmin) && (Axmin < Bxmax + 12.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 2.0f > Bzmin) && (Azmin < Bzmax))
				{
					scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					SetDestroy();	//this -> SetDestroy thisポインターは省略も出来る
					return;
				}
			}

		}
	}


	for (YokoBlock* yokoform : yokoList) //岩の当たり判定
	{
		D3DXVECTOR3 yokoformPosition = yokoform->GetPosition();
		D3DXVECTOR3 yokoformScale = yokoform->GetScale();


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

		if ((Axmax + 80.0f > Bxmin) && (Axmin < Bxmax + 80.0f))
		{
			if ((Aymin < Bymax) && (Aymax > Bymin))
			{
				if ((Azmax + 2.0f > Bzmin) && (Azmin < Bzmax))
				{
					scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					SetDestroy();	//this -> SetDestroy thisポインターは省略も出来る
					return;
				}
			}

		}
	}

	for (TateBlock* tateblockform : tateblockList) //ブロックの当たり判定
	{
		D3DXVECTOR3 tateblockformPosition = tateblockform->GetPosition();
		D3DXVECTOR3 tateblockformScale = tateblockform->GetScale();


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

		if ((Axmax + 2.0f > Bxmin) && (Axmin < Bxmax + 2.0f))
		{
			if ((Aymin < Bymax + 1.0f) && (Aymax + 1.0f > Bymin))
			{
				if ((Azmax + 60.0f > Bzmin) && (Azmin < Bzmax + 60.0f))
				{
					scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
					SetDestroy();	//this -> SetDestroy thisポインターは省略も出来る
					return;
				}
			}
		}
	}

	for (TateBlockObb* tateblockobbform : tateblockobbList) //ブロックの当たり判定
	{
		D3DXVECTOR3 tateblockobbformPosition = tateblockobbform->GetPosition();
		D3DXVECTOR3 tateblockobbformScale = tateblockobbform->GetScale();


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
			scene->AddGameObject<Explosion>(1)->SetPosition(m_Position);
			SetDestroy();	//this -> SetDestroy thisポインターは省略も出来る
			return;
		}
	}

	CarEnemy* carenemy = scene->GetGameObject<CarEnemy>(1);
     m_EnemyPosition = carenemy->GetPosition();

   
   m_DirPosition.x = m_EnemyPosition.x - m_Position.x;	//向き
   m_DirPosition.z = m_EnemyPosition.z - m_Position.z;

   D3DXVec3Normalize(&m_DirPosition, &m_DirPosition); //正規化

   
   m_Position.x += m_DirPosition.x, * m_Velocity;	//赤こうらの移動
   m_Position.z += m_DirPosition.z, * m_Velocity;

}


void Koura::Draw()
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
