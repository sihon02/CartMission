#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"
#include "ChageUi.h"
#include "camera.h"
#include "input.h"

#define TEXTURE_WIDTH	(200)	// �e�N�X�`���T�C�Y
#define TEXTURE_HEIGHT	(200)	 
#define TEXTURE_DRAW	(1)		// ����
#define CHARGE_MAX		(9)	
#define CHARGE_MIN		(0)			    

void ChargeUi::Init()
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

	//���_�o�b�t�@����
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

	// �e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(Renderer::GetDevice(),
		"asset/texture/karigage.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	Renderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "unlitTextureVS.cso");

	Renderer::CreatePixelShader(&m_PixelShader, "unlitTexturePS.cso");

	m_Position = D3DXVECTOR3(850.0f, 450.0f, 0.0f);
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);

	m_ChargeUi = 0;

}


void ChargeUi::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();

	m_VertexLayout->Release();
	m_VertexShader->Release();
	m_PixelShader->Release();

}


void ChargeUi::Update()
{
	if (m_ChargeUi > CHARGE_MAX)
	{
		m_ChargeUi = CHARGE_MAX;
	}

	if (m_ChargeUi < CHARGE_MIN)
	{
		m_ChargeUi = CHARGE_MIN;
	}
}


void ChargeUi::Draw()
{
	//�e�N�X�`�����W�Z�o
	int number = m_ChargeUi;
	for (int i = 0; i < TEXTURE_DRAW; i++)
	{
		float x = (float)(number % 5);
		float y = (float)(number % 2);

		//�摜�̈ʒu��e�N�X�`���[���W�𔽉f
		float px = m_Position.x - m_W * i;	//�\���ʒuX
		float py = m_Position.y - m_H * i;	//�\���ʒuY
		float pw = m_W;				//�\����
		float ph = m_H;				//�\������

		float tw = 1.0f / 5;		// �e�N�X�`���̕�
		float th = 1.0f / 2;		// �e�N�X�`���̍���
		float tx = x * tw;			// �e�N�X�`���̍���X���W
		float ty = y * th;			// �e�N�X�`���̍���Y���W

	//���_�f�[�^��������
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

		//���̓��C�A�E�g�ݒ�
		Renderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);

		//�V�F�[�_�[�ݒ�
		Renderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
		Renderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

		//�}�g���b�N�X�ݒ�
		Renderer::SetWorldViewProjection2D();

		//���_�o�b�t�@�ݒ�
		UINT stride = sizeof(VERTEX_3D);
		UINT offset = 0;
		Renderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);

		//�}�e���A���ݒ�
		MATERIAL material;
		ZeroMemory(&material, sizeof(material));
		material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		Renderer::SetMaterial(material);

		//�e�N�X�`���ݒ�
		Renderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

		//�v���~�e�B�u�g�|���W�ݒ�
		Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		//�|���S���`��
		Renderer::GetDeviceContext()->Draw(4, 0);

	}

}
