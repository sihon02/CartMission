#pragma once

#include "Scene.h"

class Result : public Scene
{
private:
	class Transition* m_Transition;
	class TransitionStageSelect* m_TransitionStageSelect;
	class Audio* m_ShotSE;
	class Audio* m_ShotSE1;

	int m_Direction;

public:
	void Init();
	void Uninit();
	void Update();


};

