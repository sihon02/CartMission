#pragma once

#include "GameObject.h"

class GameOverCursor : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	float m_W;	//表示幅
	float m_H;	//表示高さ

	int m_Cursor;

	bool m_Selctflag;
	bool m_Titleflag;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGameflag() { return m_Selctflag; }
	bool GetGame2flag() { return m_Titleflag; }

};