#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "renderer.h"
#include "model.h"
#include "GoalLineStage2.h"
#include "Player.h"
#include "CarEnemy.h"
#include "GoalCountUi.h"
#include "EnemyCountUi.h"


void GoalLineStage2::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\goalyuka.obj");

	//VERTEX_3D vertex[4];

	m_Position = D3DXVECTOR3(-28.0f, 0.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(40.0f, 2.0f, 2.0f);
	m_Routine = 0;
	m_Goal = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}


void GoalLineStage2::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void GoalLineStage2::Update()
{



	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>(1);
	CarEnemy* carenemy = scene->GetGameObject<CarEnemy>(1);
	GoalCountUi* goalcount = scene->GetGameObject<GoalCountUi>(2);
	EnemyCountUi* enemycount = scene->GetGameObject<EnemyCountUi>(2);

	std::vector<Player*> playerList = scene->GetGameObjects<Player>(1);
	std::vector<CarEnemy*> carenemyList = scene->GetGameObjects<CarEnemy>(1);

	for (Player* playerform : playerList) //岩の当たり判定
	{
		D3DXVECTOR3 playerformPosition = playerform->GetPosition();
		D3DXVECTOR3 playerformScale = playerform->GetScale();


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = playerformPosition.x + (playerformScale.x / 2);
		float Bxmin = playerformPosition.x - (playerformScale.x / 2);
		float Bymax = playerformPosition.y + (playerformScale.y / 2);
		float Bymin = playerformPosition.y - (playerformScale.y / 2);
		float Bzmax = playerformPosition.z + (playerformScale.z / 2);
		float Bzmin = playerformPosition.z - (playerformScale.z / 2);

		if ((Axmax + 5.0f > Bxmin) && (Axmin < Bxmax + 5.0f))
		{
			if ((Azmax + 1.0f > Bzmin) && (Azmin < Bzmax + 1.0f))
			{
				if (player->GetCheckPoint())	//チェックポイントを通過していたらカウントを追加する
				{
					m_Routine += 1;
					player->SetCheckPoint(false);

					if (m_Routine < 4)
					{
						goalcount->AddCount(1);
					}
				}

				return;
			}
		}
	}

	for (CarEnemy* carenemyform : carenemyList) //岩の当たり判定
	{
		D3DXVECTOR3 carenemyformPosition = carenemyform->GetPosition();
		D3DXVECTOR3 carenemyformScale = carenemyform->GetScale();


		float Axmax = m_Position.x + (m_Scale.x / 2);
		float Axmin = m_Position.x - (m_Scale.x / 2);
		float Aymax = m_Position.y + (m_Scale.y / 2);
		float Aymin = m_Position.y - (m_Scale.y / 2);
		float Azmax = m_Position.z + (m_Scale.z / 2);
		float Azmin = m_Position.z - (m_Scale.z / 2);

		float Bxmax = carenemyformPosition.x + (carenemyformScale.x / 2);
		float Bxmin = carenemyformPosition.x - (carenemyformScale.x / 2);
		float Bymax = carenemyformPosition.y + (carenemyformScale.y / 2);
		float Bymin = carenemyformPosition.y - (carenemyformScale.y / 2);
		float Bzmax = carenemyformPosition.z + (carenemyformScale.z / 2);
		float Bzmin = carenemyformPosition.z - (carenemyformScale.z / 2);

		if ((Axmax + 1.0f > Bxmin) && (Axmin < Bxmax + 1.0f))
		{
			if ((Azmax - 1.2f > Bzmin) && (Azmin < Bzmax - 1.2f))
			{
				if (carenemy->GetCheckPointEnemy())	//チェックポイントを通過していたらカウントを追加する
				{
					m_EnemyRoutine += 1;
					carenemy->SetCheckPointEnemy(false);
					
					if (m_EnemyRoutine < 4)
					{
						enemycount->AddCount(1);
					}
				}

				return;
			}
		}
	}

	if (m_Routine == 4)
	{
		m_Goal = true;
	}

	if (m_EnemyRoutine == 4)
	{
		m_EnemyGoal = true;
	}

}


void GoalLineStage2::Draw()
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

