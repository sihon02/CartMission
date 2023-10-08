#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "GameObject.h"



class Scene
{
protected:
	//GameObject* m_GameObject[4];
	std::list<GameObject*> m_GameObject[3];	//���X�g�\��

public:
	Scene() {}
	virtual ~Scene(){}

	virtual void Init() = 0;

	template <typename T> //�e���v���[�g�֐�
	T* AddGameObject(int Layer)
	{
		T* gameObject = new T();
		m_GameObject[Layer].push_back(gameObject);
		gameObject->Init();

		return gameObject;
	}

	template <typename T>
	T* GetGameObject(int Layer)
	{
		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T)) //�^�𒲂ׂ�(RTTI���I�^���)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int Layer) //�������镨�͂�����g��
	{
		std::vector<T*> objects; //STL�̔z��

		for (GameObject* object : m_GameObject[Layer])
		{
			if (typeid(*object) == typeid(T))
			{
				objects.push_back((T*)object);
			}
		}
		
		return objects;
	}

	virtual void Uninit()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Uninit();
				delete object;
			}
			m_GameObject[i].clear(); //���X�g�̃N���A
		}	
		/*for (int i = 0; i < 0; i++)
		{
			m_GameObject[i]->Uninit();
			delete m_GameObject[i];
		}*/
	}

	virtual void Update()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i]) //�͈�for���[�v
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy(); });
		}
	
		//�����_��


		//for (int i = 0; i < 4; i++)
		//{
		//	m_GameObject[i]->Update(); // �|�����t�B�Y���i���Ԑ��j
		//}
	}

	virtual void Draw()
	{
		for (int i = 0; i < 3; i++)
		{
			for (GameObject* object : m_GameObject[i])
			{
				object->Draw();
			}
		}
		//for (int i = 0; i < 4; i++)
		//{
		//	m_GameObject[i]->Draw(); // �|�����t�B�Y���i���Ԑ��j
		//}
	}

};
