#pragma once

#include "Scene.h"
// Klasa do wy�wietlania zasad gry
class ControlScene : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);
};
