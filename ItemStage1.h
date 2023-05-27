#pragma once

#include "GameObject.h"

class ItemStage1 : public GameObject	//åpè≥
{

private:

	Model* m_Model;	//ÉÇÉfÉãÇì«Ç›çûÇﬁóp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;


	class Audio* m_ShotSE;
	class Audio* m_ShotSE2;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};