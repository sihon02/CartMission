#include "main.h"
#include "renderer.h"
#include "model.h"
#include "BlockEnemy.h"
#include "Koura.h"
#include "Scene.h"
#include "manager.h"

void BlockEnemy::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\failblock.obj");

	//VERTEX_3D vertex[4];

	m_Position = D3DXVECTOR3(5.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, D3DX_PI * 2, D3DX_PI);
	m_Scale = D3DXVECTOR3(4.0f, 4.0f, 4.0f);

	m_Time = 0;
	m_TimeFlag = false;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

}


void BlockEnemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void BlockEnemy::Update()
{
	m_Time += 1;

	if (m_Time >= 300)
	{
		m_TimeFlag = true;
	}

	if (m_TimeFlag == true)
	{
		Scene* scene = Manager::GetScene();

		scene->AddGameObject<Koura>(1)->SetPosition(m_Position);

		m_TimeFlag = false;
		m_Time = 0;
	}
}


void BlockEnemy::Draw()
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
