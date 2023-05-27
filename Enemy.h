#pragma once

#include "GameObject.h"

class Enemy : public GameObject	//継承
{

private:

	Model* m_Model;	//モデルを読み込む用

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//速度
	D3DXVECTOR3		m_Direction;		// 移動方向

	int m_State;

	float m_Speed;		// 移動スピード

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