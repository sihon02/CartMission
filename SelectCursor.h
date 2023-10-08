#pragma once

#include "GameObject.h"

class SelectCursor : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	float m_W;	//�\����
	float m_H;	//�\������
	
	int m_Cursor;

	bool m_Stage1flag;
	bool m_Stage2flag;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameflag() { return m_Stage1flag; }
	bool GetGame2flag() { return m_Stage2flag; }

};