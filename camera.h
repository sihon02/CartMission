#pragma once

#include "GameObject.h"

class Camera : public GameObject
{

private:

	D3DXVECTOR3 m_Target;
	D3DXMATRIX m_ViewMatrix;
	D3DXVECTOR3 m_Rotation;
	D3DXMATRIX m_ProjectionMatrix;


public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	D3DXMATRIX GetViewMatrix() { return m_ViewMatrix; }
	bool CheckView(D3DXVECTOR3 Position);

};