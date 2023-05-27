#pragma once

#include "GameObject.h"

class TransitionStage2 : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Count;
	bool m_In;
	bool m_Finish;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Start(bool In)
	{
		m_In = In;
		m_Finish = false;

		if (m_In)
			m_Count = 60;
		else
			m_Count = 0;

	};

	bool GetFinish() { return m_Finish; }

};