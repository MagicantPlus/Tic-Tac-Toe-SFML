#pragma once

#include <iostream>
#include <vector>
#include <utility>
#include "Global.h"
#include "Grid.h"
#include "Player.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
	
	const int playerNameScoreDistance = 10;
	const int roundEndDelayInFrames = 30;
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::Cursor cursor;
	cell* selectedCell;
	bool playerTurn;
	bool roundStartingPlayer;
	Player players[2];
	Grid grid;
	int currentRoundEndDelay;

	// initializers

	void initVariables();
	void initWindow();
	void initPlayers();

public:
	Game();
	virtual ~Game();

	// getters

	const Grid* getGrid() const;
	cell** getSelectedCell();
	const bool running() const;

	// setters



	// mouse functions

	const std::pair <cell*, bool> findHoveredOnCell(sf::Event::MouseMoveEvent mouseEvent);
	const bool mouseOnCell(cell cell, sf::Event::MouseMoveEvent mouseEvent) const;

	// event processing

	void processClosedEvent();
	void processMouseMoveEvent(sf::Event::MouseMoveEvent mouseEvent);
	void processMouseButtonPressedEvent(sf::Event::MouseButtonEvent mouseEvent);

	// text functions

	void updatePlayersTextPositions();

	// round functions

	void switchStartingPlayer();
	void checkRoundEnd();
	void playerWin(Player& player);
	void roundDraw();

	// game loop

	void pollEvents();
	void update();
	void render();
};

