#pragma once

#include "GameObject.h"

class StartTime : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Count;
	float m_Time;		//Žc‚èŽžŠÔ
	bool m_UseTimeflag;
	bool m_Drawflag;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void AddCount(int Count) { m_Count += Count; }

};