#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"
#include "model.h"
#include "Banana.h"
#include "Player.h"
#include "CarEnemy.h"
#include "explosion.h"
#include "audio.h"


void Banana::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\banana.obj");

	m_Position = D3DXVECTOR3(8.0f, 3.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.5f, 1.5f, 1.5f);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	Scene* scene = Manager::GetScene();
	m_ShotSE = scene->AddGameObject<Audio>(2);
	m_ShotSE->Load("asset\\audio\\key.wav");
	m_ShotSE2 = scene->AddGameObject<Audio>(2);
	m_ShotSE2->Load("asset\\audio\\hit.wav");

}


void Banana::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Banana::Update()
{

	Scene* scene = Manager::GetScene();
	std::vector<Player*> playerList = scene->GetGameObjects<Player>(1);
	std::vector<CarEnemy*> carenemyList = scene->GetGameObjects<CarEnemy>(1);

	for (Player* player : playerList)  //アイテムの当たり判定
	{
		D3DXVECTOR3 playerPosition = player->GetPosition();

		D3DXVECTOR3 direction = m_Position - playerPosition;
		float length = D3DXVec3Length(&direction);

		if (length < 5.0f)
		{
			m_ShotSE->Play();
			scene->AddGameObject<Explosion>(1)->SetPosition(playerPosition);
			SetDestroy();	//当たったら消える
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
			//m_ShotSE2->Play();
			scene->AddGameObject<Explosion>(1)->SetPosition(carenemyPosition);
			SetDestroy();	//当たったら消える
			return;
		}
	}
}


void Banana::Draw()
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
