#include "main.h"
#include "renderer.h"
#include "model.h"
#include "Enemy.h"
#include "Scene.h"
#include "manager.h"

void Enemy::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\failblock.obj");

	//VERTEX_3D vertex[4];

	m_Position = D3DXVECTOR3(5.0f, 3.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, -D3DX_PI * 0.5, D3DX_PI);
	m_Scale = D3DXVECTOR3(4.5f, 4.5f, 4.5f);
	m_Velocity = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Direction = D3DXVECTOR3(frand() - 0.5f, 0.0f, frand() - 0.5f);
	m_Speed = 0.5f;

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}


void Enemy::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void Enemy::Update()
{
	State();

	m_State = MOVE;

}


void Enemy::Draw()
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


void Enemy::State()
{
	switch (m_State)
	{
	case WAIT:
		Wait();
		break;
	case MOVE:
		Move();
		break;
	}
}

void Enemy::Wait()
{
	
}

void Enemy::Move()
{
	m_Position += m_Direction * m_Speed;

	if (m_Position.x > 500.0f)
		m_Direction.x *= -1;
	if (m_Position.z > 300.0f)
		m_Direction.z *= -1;
	if (m_Position.x < 200.0f)
		m_Direction.x *= -1;
	if (m_Position.z < 250.0f)
		m_Direction.z *= -1;
}

