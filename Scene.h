#pragma once

#include <list>
#include <vector>
#include <typeinfo>
#include "GameObject.h"



class Scene
{
protected:
	//GameObject* m_GameObject[4];
	std::list<GameObject*> m_GameObject[3];	//リスト構造

public:
	Scene() {}
	virtual ~Scene(){}

	virtual void Init() = 0;

	template <typename T> //テンプレート関数
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
			if (typeid(*object) == typeid(T)) //型を調べる(RTTI動的型情報)
			{
				return (T*)object;
			}
		}
		return NULL;
	}

	template <typename T>
	std::vector<T*> GetGameObjects(int Layer) //複数ある物はこれを使う
	{
		std::vector<T*> objects; //STLの配列

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
			m_GameObject[i].clear(); //リストのクリア
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
			for (GameObject* object : m_GameObject[i]) //範囲forループ
			{
				object->Update();
			}

			m_GameObject[i].remove_if([](GameObject* object)
				{return object->Destroy(); });
		}
	
		//ラムダ式


		//for (int i = 0; i < 4; i++)
		//{
		//	m_GameObject[i]->Update(); // ポリモフィズム（多態性）
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
		//	m_GameObject[i]->Draw(); // ポリモフィズム（多態性）
		//}
	}

};
