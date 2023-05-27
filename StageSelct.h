#pragma once

#include "Scene.h"

class StageSelct : public Scene
{
private:
	class TransitionStage1* m_TransitionStage1;
	class TransitionStage2* m_TransitionStage2;
	class Transition* m_Transition;
	class Audio* m_ShotSE;
	class Audio* m_ShotSE1;


	int m_Direction;

public:
	void Init();
	void Uninit();
	void Update();


};
