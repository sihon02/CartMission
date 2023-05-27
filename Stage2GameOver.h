#pragma once

#include "Scene.h"

class Stage2GameOver : public Scene
{
private:
	class TransitionStage2* m_TransitionStage2;
	class TransitionStageSelect* m_TransitionStageSelect;
	class Audio* m_ShotSE;
	class Audio* m_ShotSE1;

	int m_Direction;

public:
	void Init();
	void Uninit();
	void Update();


};

