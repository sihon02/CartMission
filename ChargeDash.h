#pragma once

#include "GameObject.h"

class ChargeDash : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Count;

	class Audio* m_ShotSE;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};