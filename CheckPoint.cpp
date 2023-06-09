#include "main.h"
#include "manager.h"
#include "Scene.h"
#include "renderer.h"
#include "model.h"
#include "CheckPoint.h"
#include "Player.h"


void CheckPoint::Init()
{
	m_Model = new Model();
	m_Model->Load("asset\\Model\\jumpdai.obj");

	//VERTEX_3D vertex[4];

	m_Position = D3DXVECTOR3(5.0f, 1.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, D3DX_PI * 0.05f, 0.0f);
	m_Scale = D3DXVECTOR3(2.0f, 1.5f, 1.5f);


	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexLightingVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "vertexLightingPS.cso");

}


void CheckPoint::Uninit()
{
	m_Model->Unload();
	delete m_Model;

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void CheckPoint::Update()
{



}


void CheckPoint::Draw()
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

