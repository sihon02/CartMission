#pragma once

#include "GameObject.h"

class Item : public GameObject	//�p��
{

private:

	Model* m_Model;	//���f����ǂݍ��ޗp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;
	

	class Audio* m_ShotSE;
	class Audio* m_ShotSE2;

	int m_Num;	//�A�C�e���̔ԍ��p

	void ItemType();

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


	enum ItemType
	{
		KINOKO, KINOKO2, KINOKO3, KOURA
	};


};