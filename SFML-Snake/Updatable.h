#pragma once

// Klasa abstrakcyjna dla obiekt�w aktualizowanych co klatk�
class Updatable
{
public:
	virtual void Update(float deltaTime) = 0;
};