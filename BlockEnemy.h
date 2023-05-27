#pragma once

#include "GameObject.h"

class BlockEnemy : public GameObject	//�p��
{

private:

	Model* m_Model;	//���f����ǂݍ��ޗp

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