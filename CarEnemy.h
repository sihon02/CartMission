#pragma once

#include "GameObject.h"
#include "model.h"

class CarEnemy : public GameObject	//�p��
{

private:

	class Model* m_Model;	//���f����ǂݍ��ޗp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//���x
	D3DXVECTOR3 m_TargetRotation;//�p�x
	D3DXVECTOR3 m_PlayerPosition;//�v���C���[���W
	D3DXVECTOR3 m_DirPosition;


	int m_ItemUse;
	int m_Time;
	int m_Direction;

	float m_UseTime;
	

	bool m_UseTimeflag;
	bool m_RedKouraflag;			//�Ԃ�����������Ă��邩�̔���
	bool m_isTunrderEnemyflag;		//�T���_�[���g�p�������̔���

	bool m_isCheckPointEnemy;		//�`�F�b�N�|�C���g��ʉ߂��Ă��邩�̔���

	int m_State;

	class Audio* m_ShotSE;

	void State();
	void Wait();
	void Move();
	void Attack();

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetItemUse(int ItemUse)
	{
		m_ItemUse = ItemUse;
	}

	void SetCheckPointEnemy(bool isCheckPointEnemy)
	{
		m_isCheckPointEnemy = isCheckPointEnemy;
	}

	void IsRedKoura(bool Start)
	{
		m_RedKouraflag = Start;

		if (m_RedKouraflag)
			m_Time = 60;
		else
			m_Time = 0;

	};

	void IsThunderEnemy(bool Start)
	{
		m_isTunrderEnemyflag = Start;

		if (m_isTunrderEnemyflag)
			m_Time = 60;
		else
			m_Time = 0;

	};

	bool GetCheckPointEnemy()
	{
		return m_isCheckPointEnemy;
	}

	enum CarEnemyState
	{
		WAIT, MOVE , ATTACK
	};


};