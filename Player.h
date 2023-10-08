#pragma once

#include "GameObject.h"
#include "model.h"

class Player : public GameObject	//�p��
{

private:

	class Model* m_Model;	//���f����ǂݍ��ޗp

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//���x
	D3DXVECTOR3 m_TargetRotation;//�p�x

	int m_ItemType;
	int m_JumpUse;
	int m_Time;

	float m_StartTime;
	float m_Charge;		//�`���[�W�l

	bool m_StartTimeflag;
	bool m_Tunrderflag;
	bool m_Bnanaflag;
	bool m_isClash;
	bool m_isAccele;			//�A�N�Z����������Ă邩�̔���
	bool m_isThunder;			//�T���_�[�������Ă��邩�̔���
	bool m_isCheckPoint;		//�`�F�b�N�|�C���g��ʉ߂������̔���

	class Audio* m_ShotSE;
	class Audio* m_ShotSE2;
	class Audio* m_ShotSE3;
	class Shadow* m_Shadow;

public:
	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetItemUse(int ItemType)
	{
		m_ItemType = ItemType;
	}

	void IsThunder(bool Start)
	{
		m_Tunrderflag = Start;

		if (m_Tunrderflag)
			m_Time = 60;
		else
			m_Time = 0;

	};

	bool GetCheckPoint() //�`�F�b�N�|�C���g��ʉ߂��Ă���true�ɂ��ăS�[���J�E���g��ǉ�����
	{
		return m_isCheckPoint; 
	}

	void SetCheckPoint(bool isCheckPoint)
	{
		m_isCheckPoint = isCheckPoint;
	}

};