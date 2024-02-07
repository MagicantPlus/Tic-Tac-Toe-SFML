#include "Grid.h"

Grid::Grid()
{
	this->initGridLines();
	this->initCells();
}

Grid::~Grid()
{

}

// initializers

void Grid::initGridLines()
{
	gridLines.resize(4);

	this->gridLines[0].setPosition((GRIDSPACE_WIDTH - 2 * gridlineShort) / 3 + GRID_WIDTH_DELTA, GRID_HEIGHT_UP_DELTA);
	this->gridLines[0].setSize(sf::Vector2f(gridlineShort, gridlineLong));
	this->gridLines[0].setFillColor(sf::Color(0, 0, 0, 255));

	this->gridLines[1].setPosition((GRIDSPACE_WIDTH - 2 * gridlineShort) / 3 * 2 + gridlineShort + GRID_WIDTH_DELTA, GRID_HEIGHT_UP_DELTA);
	this->gridLines[1].setSize(sf::Vector2f(gridlineShort, gridlineLong));
	this->gridLines[1].setFillColor(sf::Color(0, 0, 0, 255));

	this->gridLines[2].setPosition(GRID_WIDTH_DELTA, (GRIDSPACE_HEIGHT - 2 * gridlineShort) / 3 + GRID_HEIGHT_UP_DELTA);
	this->gridLines[2].setSize(sf::Vector2f(gridlineLong, gridlineShort));
	this->gridLines[2].setFillColor(sf::Color(0, 0, 0, 255));

	this->gridLines[3].setPosition(GRID_WIDTH_DELTA, (GRIDSPACE_WIDTH - 2 * gridlineShort) / 3 * 2 + gridlineShort + GRID_HEIGHT_UP_DELTA);
	this->gridLines[3].setSize(sf::Vector2f(gridlineLong, gridlineShort));
	this->gridLines[3].setFillColor(sf::Color(0, 0, 0, 255));
}

void Grid::initCells()
{
	this->cells.resize(9);

	const float startX1 = GRID_WIDTH_DELTA;
	const float startY1 = GRID_HEIGHT_UP_DELTA;
	const float startX2 = this->gridLines[0].getPosition().x - 1;
	const float startY2 = this->gridLines[2].getPosition().y - 1;
	const float xJump = this->gridLines[0].getPosition().x - 1 + gridlineShort - GRID_WIDTH_DELTA + 1;
	const float yJump = this->gridLines[2].getPosition().y - 1 + gridlineShort - GRID_HEIGHT_UP_DELTA + 1;
	const float XSHAPE_X_DELTA = CELL_LENGTH - 2 * XSHAPE_WIDTH_DELTA - XSHAPE_SHORT / sqrt(2);
	const float XSHAPE_Y_DELTA = CELL_LENGTH - 2 * XSHAPE_HEIGHT_DELTA - XSHAPE_SHORT / sqrt(2);

	XSHAPE_LONG = sqrt(XSHAPE_X_DELTA * XSHAPE_X_DELTA + XSHAPE_Y_DELTA * XSHAPE_Y_DELTA);

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			this->cells[i * 3 + j].x[0] = startX1 + xJump * j;
			this->cells[i * 3 + j].y[0] = startY1 + yJump * i;
			this->cells[i * 3 + j].x[1] = startX2 + xJump * j;
			this->cells[i * 3 + j].y[1] = startY2 + yJump * i;
			this->cells[i * 3 + j].state = -1;

			this->cells[i * 3 + j].xShape[0].setFillColor(sf::Color(0, 0, 0, 255));
			this->cells[i * 3 + j].xShape[1].setFillColor(sf::Color(0, 0, 0, 255));
			this->cells[i * 3 + j].xShape[0].setPosition(this->cells[i * 3 + j].x[0] + XSHAPE_SHORT / sqrt(2) + XSHAPE_WIDTH_DELTA, this->cells[i * 3 + j].y[0] + XSHAPE_HEIGHT_DELTA);
			this->cells[i * 3 + j].xShape[1].setPosition(this->cells[i * 3 + j].x[0] + CELL_LENGTH - XSHAPE_WIDTH_DELTA, this->cells[i * 3 + j].y[0] + XSHAPE_HEIGHT_DELTA + XSHAPE_SHORT / sqrt(2));
			this->cells[i * 3 + j].xShape[0].setSize(sf::Vector2f(XSHAPE_LONG, XSHAPE_SHORT));
			this->cells[i * 3 + j].xShape[1].setSize(sf::Vector2f(XSHAPE_LONG, XSHAPE_SHORT));
			this->cells[i * 3 + j].xShape[0].setRotation(45.f);
			this->cells[i * 3 + j].xShape[1].setRotation(135.f);

			this->cells[i * 3 + j].oShape.setPosition(this->cells[i * 3 + j].x[0] + OSHAPE_WIDTH_DELTA, this->cells[i * 3 + j].y[0] + OSHAPE_HEIGHT_DELTA);
			this->cells[i * 3 + j].oShape.setRadius((this->cells[i * 3 + j].x[1] - this->cells[i * 3 + j].x[0] - OSHAPE_WIDTH_DELTA * 2) / 2);
			this->cells[i * 3 + j].oShape.setFillColor(sf::Color(255, 255, 255, 0));
			this->cells[i * 3 + j].oShape.setOutlineColor(sf::Color(0, 0, 0, 255));
			this->cells[i * 3 + j].oShape.setOutlineThickness(OSHAPE_OUTLINE_THICKNESS);
		}
	}
}

// getters

std::vector <sf::RectangleShape> Grid::getGridLines()
{
	return this->gridLines;
}

std::vector <cell> Grid::getCells()
{
	return this->cells;
}

std::vector <sf::RectangleShape>* Grid::getrefGridLines()
{
	return &this->gridLines;
}

std::vector <cell>* Grid::getrefCells()
{
	return &this->cells;
}

// setters



// grid functions

void Grid::reset()
{
	for (auto& cell : cells)
	{
		cell.state = -1;
	}
}
