#pragma once

#include "GameObject.h"

class GoalLineStage1 : public GameObject	//継承
{

private:

	Model* m_Model;	//モデルを読み込む用

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Routine; //ゴールを通った数

	bool m_Goal;   //プレイヤーが３周ゴールしたかどうか

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGoal() { return m_Goal; }
};
