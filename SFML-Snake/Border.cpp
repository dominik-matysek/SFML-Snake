#include "Border.h"
#include "Engine.h"

Border::Border(sf::Vector2i gridSize, sf::Vector2i gameArea)
{
	Engine* engine = Engine::GetInstance();
	float cellSize = engine->GetCellSize();

	_gridSize = gridSize;

	// Lewo góra => prawo góra
	for (int x = 0; x < _gridSize.x - 1; ++x)
	{
		AddCell(cellSize, x * cellSize, 0);
	}

	// Prawo góra => prawo dó³
	for (int y = 0; y < _gridSize.y - 1; ++y)
	{
		AddCell(cellSize, gameArea.x - cellSize, y * cellSize);
	}

	// Prawo dó³ => lewo dó³
	for (int x = _gridSize.x - 1; x > 0; --x)
	{
		AddCell(cellSize, x * cellSize, gameArea.y - cellSize);
	}

	// Lewo dó³ => prawo góra
	for (int y = 0; y < _gridSize.y; ++y)
	{
		AddCell(cellSize, 0, y * cellSize);
	}

	// Dodatkowe warstwy

	for (int x = 0; x < _gridSize.x - 1; ++x)
	{
		AddCell(cellSize, x * cellSize, gameArea.y - 2 * cellSize);
	}

	for (int y = 0; y < _gridSize.y - 1; ++y)
	{
		AddCell(cellSize, gameArea.x - 2 * cellSize, y * cellSize);
	}

	for (int x = _gridSize.x - 1; x > 0; --x)
	{
		AddCell(cellSize, x * cellSize, gameArea.y - 24 * cellSize);
	}

	for (int y = 0; y < _gridSize.y; ++y)
	{
		AddCell(cellSize, gameArea.x - 39 * cellSize, y * cellSize);
	}
}

// Dojdzie do kolizji je¿eli postaæ gracza znajdzie siê na tej samej pozycji, na której znajduje siê granica
bool Border::Collides(sf::Vector2i gridPosition) const
{
	return gridPosition.x == 0 || gridPosition.x == _gridSize.x - 1 || gridPosition.x == _gridSize.x - 2 || gridPosition.x == 1
		|| gridPosition.y == 0 || gridPosition.y == _gridSize.y - 1 || gridPosition.y == 1 || gridPosition.y == _gridSize.y - 2;
}

void Border::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (size_t i = 0; i < _cells.size(); ++i)
	{
		target.draw(*_cells[i]);
	}
}

void Border::AddCell(float cellSize, float posX, float posY)
{
	std::shared_ptr<sf::RectangleShape> cell = std::make_shared<sf::RectangleShape>(sf::Vector2f(cellSize, cellSize));

	// Co druga kratka granicy ma ten sam kolor, kratki obok siebie ró¿ni¹ siê kolorem
	cell->setFillColor(_colors[_cells.size() % _colors.size()]);
	cell->setPosition(posX, posY);
	_cells.push_back(cell);
}