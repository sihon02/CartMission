#pragma once

#include "Scene.h"

class Stage2 : public Scene
{
private:
	class TransitionStageSelect* m_TransitionStageSelect;

public:
	void Init();
	void Uninit();
	void Update();

	class GoalLineStage2* m_Goalyuka;
};
