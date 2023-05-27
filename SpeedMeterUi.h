#pragma once

#include "GameObject.h"

class SpeedMeterUi : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_SpeedMeter;
	float m_W;			//ï\é¶ïù
	float m_H;			//ï\é¶çÇÇ≥

	float m_UseTime;
	bool m_UseTimeflag;
	bool m_Timeflag;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void AddSpeedMeter(int SpeedMeter) { m_SpeedMeter += SpeedMeter; }

	bool GetTimeflag() { return m_Timeflag; }

};