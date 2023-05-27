#pragma once

#include "GameObject.h"

class Item : public GameObject	//継承
{

private:

	Model* m_Model;	//モデルを読み込む用

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;
	

	class Audio* m_ShotSE;
	class Audio* m_ShotSE2;

	int m_Num;	//アイテムの番号用

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