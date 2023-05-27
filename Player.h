#pragma once

#include "GameObject.h"
#include "model.h"

class Player : public GameObject	//継承
{

private:

	class Model* m_Model;	//モデルを読み込む用

	ID3D11VertexShader* m_VertexShader = NULL;
	ID3D11PixelShader* m_PixelShader = NULL;
	ID3D11InputLayout* m_VertexLayout = NULL;

	D3DXVECTOR3 m_Velocity;//速度
	D3DXVECTOR3 m_TargetRotation;//角度

	int m_ItemType;
	int m_JumpUse;
	int m_Time;

	float m_StartTime;
	float m_Charge;		//チャージ値

	bool m_StartTimeflag;
	bool m_Tunrderflag;
	bool m_Bnanaflag;
	bool m_isClash;
	bool m_isAccele;			//アクセルが押されてるかの判定
	bool m_isThunder;			//サンダーをうけているかの判定
	bool m_isCheckPoint;		//チェックポイントを通過したかの判定

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

	bool GetCheckPoint() //チェックポイントを通過してたらtrueにしてゴールカウントを追加する
	{
		return m_isCheckPoint; 
	}

	void SetCheckPoint(bool isCheckPoint)
	{
		m_isCheckPoint = isCheckPoint;
	}

};