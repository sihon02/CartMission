#pragma once

#include "GameObject.h"

class FailEnemy : public GameObject	//継承
{

private:

	Model* m_Model;	//モデルを読み込む用

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//速度
	D3DXVECTOR3		m_Direction;		// 移動方向

	float			m_Speed;		// 移動スピード

	int				m_IntervalTime;

	bool			m_FailTimeflag;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};