#pragma once

class GameObject
{

protected: 
	bool		m_Destroy = false;

	D3DXVECTOR3 m_Position;
	D3DXVECTOR3 m_Rotation;
	D3DXVECTOR3 m_Scale;

public:
	GameObject() {}		//コンストラクタ
	virtual ~GameObject() {} //デストラクタ (仮想関数)

	virtual void Init() = 0;	//純粋仮想関数
	virtual void Uninit() = 0;
	virtual void Update() = 0;
 	virtual void Draw() = 0;
	
	void SetPosition(D3DXVECTOR3 Position)
	{
		m_Position = Position;
	}
	void SetRotation(D3DXVECTOR3 Rotation)
	{
		m_Rotation = Rotation;
	}
	void SetDestroy() 
	{
		m_Destroy = true; 
	}
	void SetScale(D3DXVECTOR3 Scale)
	{
		m_Scale = Scale;
	}

	D3DXVECTOR3 GetPosition() 
	{
 		return m_Position; 
	}
	D3DXVECTOR3 GetScale()
	{
		return m_Scale;
	}
	D3DXVECTOR3 GetRotation()
	{
		return m_Rotation;
	}

	D3DXVECTOR3 GetForward() //前方方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 forward;
		D3DXVECTOR3 up;
		D3DXVECTOR3 right;
		forward.x = rot._31;
		forward.y = rot._32;
		forward.z = rot._33;

		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return forward;

	}

	D3DXVECTOR3 GetRight() //右方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 right;
		right.x = rot._11;
		right.y = rot._12;
		right.z = rot._13;

		return right;

	}

	D3DXVECTOR3 GetUp() //上方向ベクトル取得
	{
		D3DXMATRIX rot;
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);
		D3DXVECTOR3 up;
		up.x = rot._21;
		up.y = rot._22;
		up.z = rot._23;

		return up;

	}

	D3DXVECTOR3 GetObbX()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		world = scale * rot;

		D3DXVECTOR3 vx;
		vx.x = world._11;
		vx.y = world._12;
		vx.z = world._13;

		return vx * 14.0f;
	}

	D3DXVECTOR3 GetObbZ()
	{
		D3DXMATRIX rot, scale, world;
		D3DXMatrixScaling(&scale, m_Scale.x, m_Scale.y, m_Scale.z);
		D3DXMatrixRotationYawPitchRoll(&rot, m_Rotation.y, m_Rotation.x, m_Rotation.z);

		world = scale * rot;

		D3DXVECTOR3 vz;
		vz.x = world._31;
		vz.y = world._32;
		vz.z = world._33;

		return vz * 5.0f;
	}

	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}
	}

	float frand(void)
	{
		return (((float)rand()) / RAND_MAX);
	}


};