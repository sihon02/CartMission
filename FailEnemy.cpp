#include "main.h"
#include "renderer.h"
#include "model.h"
#include "FailEnemy.h"
#include "Player.h"
#include "Scene.h"
#include "manager.h"

#define FailTime 0

void FailEnemy::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\failblock.obj");


	m_Position = D3DXVECTOR3(5.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5f, D3DX_PI);
	m_Scale = D3DXVECTOR3(4.0f, 4.0f, 4.0f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_IntervalTime = 80;
	m_FailTimeflag = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}


void FailEnemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void FailEnemy::Update()
{

	Scene* scene = Manager::GetScene();
	std::vector<Player*> playerList = scene->GetGameObjects<Player>(1);

	for (Player* playerform : playerList) //プレイヤーの当たり判定
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

		if ((Axmax + 30.0f > Bxmin) && (Axmin < Bxmax + 30.0f))
		{
			if ((Aymin < Bymax + 30.0f) && (Aymax + 30.0f > Bymin))
			{
				if ((Azmax + 5.0f > Bzmin) && (Azmin < Bzmax + 5.0f))
				{
					//重力
					m_Velocity.y -= 0.02f;
					m_FailTimeflag = true;
				}
			}

		}
	}


	if (m_FailTimeflag == true)
		m_IntervalTime -= 1;

	if (m_IntervalTime < FailTime)
	{
		m_FailTimeflag = false;
		m_Velocity.y += 0.03f;
	}

	if (15.0f <= m_Position.y)
	{
		m_IntervalTime = 100;
		m_Position.y = 14.0f;
		m_Velocity.y = 0.0f;
	}


	//抵抗
	m_Velocity.x -= m_Velocity.x * 0.4f;
	m_Velocity.y -= m_Velocity.y * 0.01f;
	m_Velocity.z -= m_Velocity.z * 0.4f;

	D3DXVECTOR3 oldPosition = m_Position;

	//移動
	m_Position += m_Velocity;

	float groundHeight = 5.0f;


	//接地
	if (m_Position.y < groundHeight && m_Velocity.y < 0.0f)
	{
		m_Position.y = groundHeight;
	}

}


void FailEnemy::Draw()
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
