#pragma once

#include "GameObject.h"

class GoalLineStage1 : public GameObject	//�p��
{

private:

	Model* m_Model;	//���f����ǂݍ��ޗp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	int m_Routine; //�S�[����ʂ�����

	bool m_Goal;   //�v���C���[���R���S�[���������ǂ���

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	bool GetGoal() { return m_Goal; }
};
