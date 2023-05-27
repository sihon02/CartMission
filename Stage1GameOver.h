#pragma once

#include "Scene.h"

class Stage1GameOver : public Scene
{
private:
	class TransitionStage1* m_TransitionStage1;
	class TransitionStageSelect* m_TransitionStageSelect;
	class Audio* m_ShotSE;
	class Audio* m_ShotSE1;

	int m_Direction;

public:
	void Init();
	void Uninit();
	void Update();


};

