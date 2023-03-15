#pragma once

#include <SFML/Window.hpp>
#include <map>

// Klasa do obs³ugi inputów
class InputManager
{
private:
	InputManager();

public:
	// Aktualizacja inputów
	static void Update();
	// Zwraca true je¿eli dany przycisk jest aktualnie wciœniêty
	static bool IsKeyPressed(sf::Keyboard::Key key);
	// Zwraca true je¿eli przycisk by³ wciœniêty w tej klatce, ale nie w poprzedniej
	static bool WasKeyPressedThisFrame(sf::Keyboard::Key key);

private:
	static InputManager _instance;

	// Mapa do przechowywania wartoœci wpisanego przycisku oraz wartoœci bool w zale¿noœci od tego kiedy by³ wciœniêty
	std::map<sf::Keyboard::Key, bool> _inputsPressedThisFrame;
	std::map<sf::Keyboard::Key, bool> _inputsPressed;
};