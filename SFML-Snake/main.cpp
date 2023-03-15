#include "Engine.h"
#include <iostream>

int main()
{
	Engine* game = Engine::GetInstance();

	game->Init();

	sf::Clock clock;
	while (game->IsRunning())
	{
		sf::Time deltaTime = clock.restart();

		game->UpdateInput();

		game->Update(deltaTime.asSeconds());

		game->Render();
	}

	delete game;

	return 0;
}