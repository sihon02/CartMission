#pragma once

#include "Scene.h"

class Explanation : public Scene
{
private:
	class TransitionStageSelect* m_TransitionStageSelect;
	class Audio* m_ShotSE;

public:
	void Init();
	void Uninit();
	void Update();


};
