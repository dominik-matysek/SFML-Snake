#pragma once

#include <SFML/Window.hpp>
#include <map>

// Klasa do obs�ugi input�w
class InputManager
{
private:
	InputManager();

public:
	// Aktualizacja input�w
	static void Update();
	// Zwraca true je�eli dany przycisk jest aktualnie wci�ni�ty
	static bool IsKeyPressed(sf::Keyboard::Key key);
	// Zwraca true je�eli przycisk by� wci�ni�ty w tej klatce, ale nie w poprzedniej
	static bool WasKeyPressedThisFrame(sf::Keyboard::Key key);

private:
	static InputManager _instance;

	// Mapa do przechowywania warto�ci wpisanego przycisku oraz warto�ci bool w zale�no�ci od tego kiedy by� wci�ni�ty
	std::map<sf::Keyboard::Key, bool> _inputsPressedThisFrame;
	std::map<sf::Keyboard::Key, bool> _inputsPressed;
};