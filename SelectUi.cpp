#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

#include "SelectUi.h"
#include "camera.h"
#include "input.h"

#define TEXTURE_WIDTH		(600)	// テクスチャサイズ
#define TEXTURE_HEIGHT		(600)	 
#define TEXTURE_DRAW		(1)		// 桁数


void SelctUi::Init()
{
	m_W = TEXTURE_WIDTH;
	m_H = TEXTURE_HEIGHT;

	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(200.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, 200.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(200.0f, 200.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファ生成
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	Renderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	// テクスチャ読み込み
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/selctlogo1.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Position = D3DXVECTOR3(330.0f, 300.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_Direction = 1;

	m_Drawflag = true;
}


void SelctUi::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void SelctUi::Update()
{
	if (Input::GetKeyTrigger('A') && m_Direction == 0)
	{
		m_Drawflag = true;
		m_Direction = 1;
	}

	if (Input::GetKeyTrigger('D') && m_Direction == 1)
	{
		m_Drawflag = false;
		m_Direction = 0;
	}

	if (Input::GetKeyTrigger('W'))
	{
		m_Direction = 2;
		m_Drawflag = false;
	}

	if (Input::GetKeyTrigger('S'))
	{
		m_Direction = 1;
		m_Drawflag = true;
	}

}


void SelctUi::Draw()
{
	if (m_Drawflag == true)
	{
		for (int i = 0; i < TEXTURE_DRAW; i++)
		{

			//画像の位置やテクスチャー座標を反映
			float px = m_Position.x - m_W * i;	//表示位置X
			float py = m_Position.y;			//表示位置Y
			float pw = m_W;				//表示幅
			float ph = m_H;				//表示高さ

			float tw = 1.0f;		// テクスチャの幅
			float th = 1.0f;		// テクスチャの高さ
			float tx = 1.0f;			// テクスチャの左上X座標
			float ty = 1.0f;			// テクスチャの左上Y座標

		//頂点データ書き換え
			D3D11_MAPPED_SUBRESOURCE msr;
			Renderer::GetDeviceContext()->Map(m_VertexBuffer, 0,
				D3D11_MAP_WRITE_DISCARD, 0, &msr);

			VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

			float hw, hh;
			hw = pw * 0.5f;
			hh = ph * 0.5f;

			vertex[0].Position = D3DXVECTOR3(px - hw, py - hh, 0.0f);
			vertex[0].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[0].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[0].TexCoord = D3DXVECTOR2(tx, ty);

			vertex[1].Position = D3DXVECTOR3(px + hw, py - hh, 0.0f);
			vertex[1].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[1].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[1].TexCoord = D3DXVECTOR2(tx + tw, ty);

			vertex[2].Position = D3DXVECTOR3(px - hw, py + hh, 0.0f);
			vertex[2].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[2].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[2].TexCoord = D3DXVECTOR2(tx, ty + th);

			vertex[3].Position = D3DXVECTOR3(px + hw, py + hh, 0.0f);
			vertex[3].Normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vertex[3].Diffuse = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
			vertex[3].TexCoord = D3DXVECTOR2(tx + tw, ty + th);

			Renderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

			//入力レイアウト設定
			Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

			//シェーダー設定
			Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
			Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

			//マトリックス設定
			Renderer::SetWorldViewProjection2D();

			//頂点バッファ設定
			UINT stride = sizeof(VERTEX_3D);
			UINT offset = 0;
			Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

			//マテリアル設定
			MATERIAL material;
			ZeroMemory(&material, sizeof(material));
			material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			Renderer::SetMaterial(material);

			//テクスチャ設定
			Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

			//プリミティブトポロジ設定
			Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

			//ポリゴン描画
			Renderer::GetDeviceContext()->Draw(4, 0);

		}
	}
}
