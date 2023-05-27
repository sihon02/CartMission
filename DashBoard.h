#pragma once

#include "GameObject.h"

class DashBoard : public GameObject	//åpè≥
{

private:

	Model* m_Model;	//ÉÇÉfÉãÇì«Ç›çûÇﬁóp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	ID3D11ShaderResourceView* m_Texture = NULL;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
};
