#pragma once

// Klasa abstrakcyjna dla obiektów aktualizowanych co klatkê
class Updatable
{
public:
	virtual void Update(float deltaTime) = 0;
};