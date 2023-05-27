#pragma once

#include "Scene.h"

class Stage1 : public Scene
{
public:
	void Init();
	void Uninit();
	void Update();
	
	class GoalLineStage1* m_Goalyuka;
	class TimeCountUi* m_TimeCount;
	class Transition* m_Transition;

};
