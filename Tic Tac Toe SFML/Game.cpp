#include "Game.h"
#include "Global.h"

Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initPlayers();
}

Game::~Game()
{
	delete this->window;
}

// initializers

void Game::initVariables()
{
	this->window = nullptr;
	this->playerTurn = 0;
	this->roundStartingPlayer = 0;
	this->currentRoundEndDelay = 0;
}

void Game::initWindow()
{
	this->videoMode.width = GLOBAL_VIDEO_WIDTH;
	this->videoMode.height = GLOBAL_VIDEO_HEIGHT;

	this->window = new sf::RenderWindow(videoMode, "Tic Tac Toe Game", sf::Style::Titlebar | sf::Style::Close);

	this->window->setFramerateLimit(60);
}

void Game::initPlayers()
{
	this->players[0].setName("X");
	this->players[1].setName("O");

	this->updatePlayersTextPositions();
}

// getters

const Grid* Game::getGrid() const
{
	return &this->grid;
}

cell** Game::getSelectedCell()
{
	return &this->selectedCell;
}

const bool Game::running() const
{
	return this->window->isOpen();
}

// setters



// mouse functions

const std::pair <cell*, bool> Game::findHoveredOnCell(sf::Event::MouseMoveEvent mouseEvent)
{	
	std::pair <cell*, bool> returnVal;

	for (auto& cell : *this->grid.getrefCells())
	{
		if (mouseOnCell(cell, mouseEvent))
		{
			returnVal.first = &cell;
			returnVal.second = true;
			return returnVal;
		}
	}

	returnVal.first = nullptr;
	returnVal.second = false;

	return returnVal;
}

const bool Game::mouseOnCell(cell cell, sf::Event::MouseMoveEvent mouseEvent) const
{
	if (mouseEvent.x >= cell.x[0] &&
		mouseEvent.x <= cell.x[1] &&
		mouseEvent.y >= cell.y[0] &&
		mouseEvent.y <= cell.y[1])
	{
		return true;
	}

	return false;
}

// event processing

void Game::processClosedEvent()
{
	this->window->close();
}

void Game::processMouseMoveEvent(sf::Event::MouseMoveEvent mouseEvent)
{
	for (auto& cell : *this->grid.getrefCells())
	{
		if (mouseOnCell(cell, mouseEvent)) {
			this->cursor.loadFromSystem(sf::Cursor::Hand);
			this->window->setMouseCursor(this->cursor);
			this->selectedCell = &cell;
			return;
		}
	}

	this->selectedCell = nullptr;
	this->cursor.loadFromSystem(sf::Cursor::Arrow);
	this->window->setMouseCursor(cursor);
}

void Game::processMouseButtonPressedEvent(sf::Event::MouseButtonEvent mouseEvent)
{	
	if (mouseEvent.button == sf::Mouse::Left)
	{	
		if (this->selectedCell != nullptr && this->selectedCell->state == -1)
		{
			if (this->playerTurn == 0)
			{
				this->selectedCell->state = 0;
				this->playerTurn = 1;
			}
			else
			{
				this->selectedCell->state = 1;
				this->playerTurn = 0;
			}

			if(this->currentRoundEndDelay == -1)
				this->checkRoundEnd();
		}
	}
}

// text functions

void Game::updatePlayersTextPositions()
{
	this->players[0].getrefNameTextbox()->setPosition(GLOBAL_VIDEO_WIDTH / 3 - this->players[0].getrefNameTextbox()->getLocalBounds().width / 2, GRIDSPACE_HEIGHT + GRID_HEIGHT_UP_DELTA + (GLOBAL_VIDEO_HEIGHT - GRIDSPACE_HEIGHT - GRID_HEIGHT_UP_DELTA) / 2 - (this->players[0].getrefNameTextbox()->getLocalBounds().height + this->playerNameScoreDistance + this->players[0].getrefScoreTextbox()->getLocalBounds().height) / 2);
	this->players[1].getrefNameTextbox()->setPosition(GLOBAL_VIDEO_WIDTH / 3 * 2 - this->players[1].getrefNameTextbox()->getLocalBounds().width / 2, GRIDSPACE_HEIGHT + GRID_HEIGHT_UP_DELTA + (GLOBAL_VIDEO_HEIGHT - GRIDSPACE_HEIGHT - GRID_HEIGHT_UP_DELTA) / 2 - (this->players[1].getrefNameTextbox()->getLocalBounds().height + this->playerNameScoreDistance + this->players[1].getrefScoreTextbox()->getLocalBounds().height) / 2);
	this->players[0].getrefScoreTextbox()->setPosition(GLOBAL_VIDEO_WIDTH / 3 - this->players[0].getrefScoreTextbox()->getLocalBounds().width / 2, this->players[0].getrefNameTextbox()->getPosition().y + this->players[0].getrefNameTextbox()->getLocalBounds().height + this->playerNameScoreDistance);
	this->players[1].getrefScoreTextbox()->setPosition(GLOBAL_VIDEO_WIDTH / 3 * 2 - this->players[1].getrefScoreTextbox()->getLocalBounds().width / 2, this->players[1].getrefNameTextbox()->getPosition().y + this->players[1].getrefNameTextbox()->getLocalBounds().height + this->playerNameScoreDistance);
}

// round functions

void Game::switchStartingPlayer()
{
	this->roundStartingPlayer = 1 - this->roundStartingPlayer;
}

void Game::checkRoundEnd()
{
	int occupiedCount = 0;
	Player* winner = nullptr;

	for (int i = 0; i < 3; i++)
	{	
		if ((*this->grid.getrefCells())[i * 3 + 0].state == (*this->grid.getrefCells())[i * 3 + 1].state &&
			(*this->grid.getrefCells())[i * 3 + 1].state == (*this->grid.getrefCells())[i * 3 + 2].state &&
			(*this->grid.getrefCells())[i * 3 + 1].state != -1)
		{	
			winner = &this->players[(*this->grid.getrefCells())[i * 3 + 0].state];
		}

		if ((*this->grid.getrefCells())[0 + i].state == (*this->grid.getrefCells())[3 + i].state &&
			(*this->grid.getrefCells())[3 + i].state == (*this->grid.getrefCells())[6 + i].state &&
			(*this->grid.getrefCells())[0 + i].state != -1)
		{
			winner = &this->players[(*this->grid.getrefCells())[0 + i].state];
		}
	}

	if ((*this->grid.getrefCells())[0].state == (*this->grid.getrefCells())[4].state &&
		(*this->grid.getrefCells())[4].state == (*this->grid.getrefCells())[8].state &&
		(*this->grid.getrefCells())[0].state != -1)
	{
		winner = &this->players[(*this->grid.getrefCells())[0].state];
	}

	if ((*this->grid.getrefCells())[2].state == (*this->grid.getrefCells())[4].state &&
		(*this->grid.getrefCells())[4].state == (*this->grid.getrefCells())[6].state &&
		(*this->grid.getrefCells())[2].state != -1)
	{
		winner = &this->players[(*this->grid.getrefCells())[2].state];
	}

	if (winner != NULL) {
		playerWin(*winner);
		return;
	}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if ((*this->grid.getrefCells())[i * 3 + j].state != -1)
				occupiedCount++;

	if (occupiedCount == 9)
	{
		roundDraw();
		return;
	}
}

void Game::playerWin(Player& player)
{
	player.setScore(player.getScore() + 1);
	updatePlayersTextPositions();
	
	this->currentRoundEndDelay = this->roundEndDelayInFrames;
	this->switchStartingPlayer();
	this->playerTurn = roundStartingPlayer;
}

void Game::roundDraw()
{
	this->currentRoundEndDelay = this->roundEndDelayInFrames;
	this->switchStartingPlayer();
	this->playerTurn = roundStartingPlayer;
}

// game loop

void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		switch (this->event.type) 
		{
		case sf::Event::Closed:
			this->processClosedEvent();
			break;
		case sf::Event::MouseMoved:
			processMouseMoveEvent(event.mouseMove);
			break;
		case sf::Event::MouseButtonPressed:
			processMouseButtonPressedEvent(event.mouseButton);
			break;
		}
	}
}

void Game::update()
{
	this->pollEvents();

	if (this->currentRoundEndDelay >= 1)
	{
		this->currentRoundEndDelay--;
	}
	else if (this->currentRoundEndDelay == 0)
	{
		this->grid.reset();
		this->currentRoundEndDelay = -1;
	}
}

void Game::render()
{
	this->window->clear(sf::Color(255, 255, 255, 255));

	// Draw game objects

	for (int i = 0; i < 4; i++)
	{
		this->window->draw((*this->grid.getrefGridLines())[i]);
	}

	for (auto& cell : *this->grid.getrefCells())
	{
		if (cell.state == 0)
		{
			this->window->draw(cell.xShape[0]);
			this->window->draw(cell.xShape[1]);
		}
		else if (cell.state == 1)
		{
			this->window->draw(cell.oShape);
		}
	}

	for (int i = 0; i < 2; i++)
	{
		this->window->draw(*this->players[i].getrefNameTextbox());
		this->window->draw(*this->players[i].getrefScoreTextbox());
	}

	this->window->display();
}