#pragma once

#include "GameObject.h"

class Koura : public GameObject	//åpè≥
{

private:
	static class Model* m_Model;	//ÉÇÉfÉãÇì«Ç›çûÇﬁóp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//ë¨ìx
	D3DXVECTOR3 m_PlayerPosition;
	D3DXVECTOR3 m_EnemyPosition;
	D3DXVECTOR3 m_DirPosition;

	bool m_Use;
	int m_Direction;

public:
	static void Load();
	static void Unload();

	void Init();
	void Uninit();
	void Update();
	void Draw();

};