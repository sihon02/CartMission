#pragma once

#include "GameObject.h"

class TimeCountUi : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Count;
	int m_Time;				//�c�莞��

	float m_W;				//�\����
	float m_H;				//�\������
	float m_UseTime;		//�g�p����

	bool m_UseTimeflag;
	bool m_Timeflag;	

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void AddCount(int Count) { m_Count += Count; }

	bool GetTimeflag() { return m_Timeflag; }

};