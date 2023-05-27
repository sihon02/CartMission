#pragma once

#include "GameObject.h"

class GoalCountUi : public GameObject
{

private:
	ID3D11Buffer* m_VertexBuffer = NULL;
	ID3D11ShaderResourceView* m_Texture = NULL;

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Count;	//êîéöï\é¶óp

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();
	void AddCount(int Count) { m_Count += Count; }

};