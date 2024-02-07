#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "Global.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Graphics/Color.hpp>

struct cell {
	float x[2], y[2];
	char state;
	sf::RectangleShape xShape[2];
	sf::CircleShape oShape;
};

class Grid
{
private:
	const int CELL_LENGTH = (GRIDSPACE_WIDTH - 2 * gridlineShort) / 3;
	const int XSHAPE_WIDTH_DELTA  = 20;
	const int XSHAPE_HEIGHT_DELTA = 20;
	const int XSHAPE_SHORT = gridlineShort;
	float XSHAPE_LONG;
	const int OSHAPE_WIDTH_DELTA = XSHAPE_WIDTH_DELTA;
	const int OSHAPE_HEIGHT_DELTA = XSHAPE_HEIGHT_DELTA;
	const int OSHAPE_OUTLINE_THICKNESS = XSHAPE_SHORT;

	std::vector <sf::RectangleShape> gridLines;
	std::vector <cell> cells;

	// initializers

	void initGridLines();
	void initCells();

public:
	
	Grid();
	virtual ~Grid();

	// getters

	std::vector <sf::RectangleShape> getGridLines();
	std::vector <cell> getCells();
	std::vector <sf::RectangleShape>* getrefGridLines();
	std::vector <cell>* getrefCells();

	// setters
	
	// grid functions

	void reset();
};