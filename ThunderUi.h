#pragma once

#include "GameObject.h"

class ThunderUi : public GameObject
{
private:

	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_VertexLayout;

	int m_Time;
	bool m_UseTimeflag;
	bool m_Drawflag;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void Start(bool Start)
	{
		m_Drawflag = Start;

		if (m_Drawflag)
			m_Time = 60;
		else
			m_Time = 0;

	};

};
