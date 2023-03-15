#pragma once

#include "Scene.h"

// Klasa do wyœwietlania najlepszych wyników
class ScoreBoard : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);
};
