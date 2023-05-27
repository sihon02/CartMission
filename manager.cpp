#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
//#include "Scene.h"
#include "audio.h"
#include "Stage1.h"
#include "Title.h"

Scene* Manager::m_Scene = NULL;


void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Audio::InitMaster();

	//m_Scene = new Game();
	//m_Scene->Init();

	SetScene<Title>();


}


void Manager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	Audio::UninitMaster();
	Input::Uninit();


	Renderer::Uninit();
}

void Manager::Update()
{
	Input::Update();

	m_Scene->Update();

	

}

void Manager::Draw()
{
	Renderer::Begin();

	m_Scene->Draw();



	Renderer::End();
}

