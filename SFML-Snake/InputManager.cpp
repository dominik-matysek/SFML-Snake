#include "InputManager.h"
#include "Engine.h"

InputManager InputManager::_instance{};

InputManager::InputManager()
{
	// Zapisujemy ka¿dy przycisk do mapy, z domyœln¹ wartoœci¹ przyciœniêcia = false
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
	{
		_inputsPressed.insert({ (sf::Keyboard::Key)i, false });
	}
}

void InputManager::Update()
{
	for (int i = 0; i < sf::Keyboard::KeyCount; ++i)
	{
		sf::Keyboard::Key key = (sf::Keyboard::Key)i;
		// Sprawdzamy czy u¿ytkownik ma otworzone okno gry (czy jest focus) oraz czy dany przycisk nie by³ wciœniêty poprzednio
		bool keyPressed = Engine::GetInstance()->HasFocus() && sf::Keyboard::isKeyPressed(key);
		_instance._inputsPressedThisFrame[key] = !_instance._inputsPressed[key] && keyPressed;
		_instance._inputsPressed[key] = keyPressed;
	}
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key)
{
	return _instance._inputsPressed[key];
}

bool InputManager::WasKeyPressedThisFrame(sf::Keyboard::Key key)
{
	return _instance._inputsPressedThisFrame[key];
}