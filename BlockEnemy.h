#pragma once

#include "GameObject.h"

class BlockEnemy : public GameObject	//Œp³
{

private:

	Model* m_Model;	//ƒ‚ƒfƒ‹‚ğ“Ç‚İ‚Ş—p

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Time;
	bool m_TimeFlag;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

};