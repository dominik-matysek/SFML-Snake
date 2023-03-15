#pragma once

#include "Scene.h"
#include "Snake.h"

// Klasa do wyœwietlenia sceny po œmierci gracza
class EndscreenScene : public Scene
{
public:
	virtual void Init();
	virtual void UpdateInput();
	virtual void Update(float deltaTime);

	// Tekst
	std::shared_ptr<sf::Text> menuText;
	std::shared_ptr<sf::Text> exitText;

private:
	// Sprawdzanie który przycisk jest wybrany
	bool isMenuButtonSelected = true;

	bool isExitButtonSelected = false;
};