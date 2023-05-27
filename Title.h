#pragma once

#include "Scene.h"

class Title : public Scene
{
private:

	int m_Direction;

	class TransitionStageSelect* m_TransitionStageSelect;
	class Transition* m_Transition;
	class Audio* m_ShotSE;
	class Audio* m_ShotSE1;


public:
	void Init();
	void Uninit();
	void Update();


};
