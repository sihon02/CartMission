#pragma once

#include "GameObject.h"

class Enemy : public GameObject	//�p��
{

private:

	Model* m_Model;	//���f����ǂݍ��ޗp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//���x
	D3DXVECTOR3		m_Direction;		// �ړ�����

	int m_State;

	float m_Speed;		// �ړ��X�s�[�h

	void State();
	void Wait();
	void Move();

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	enum eCarEnemyState
	{
		WAIT, MOVE
	};

};