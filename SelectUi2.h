#pragma once

#include "GameObject.h"

class SelctUi2 : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Direction;

	float m_W;	//ï\é¶ïù
	float m_H;	//ï\é¶çÇÇ≥

	bool m_Drawflag;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};