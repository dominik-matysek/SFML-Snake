#pragma once

#include "Scene.h"

// Klasa do wy�wietlania najlepszych wynik�w
class ScoreBoard : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);
};
