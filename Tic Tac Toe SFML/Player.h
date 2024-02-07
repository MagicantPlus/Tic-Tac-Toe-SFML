#pragma once

#include <string>
#include "Global.h"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{	
private:

	int TEXTBOX_CHARACTER_SIZE = 30;

	sf::Font textFont;
	sf::Text nameTextbox, scoreTextbox;
	std::string name;
	int score;

	// initializers

	void initVariables();
	void initNameTextbox();
	void initScoreTextbox();

public:

	Player();
	virtual ~Player();
	
	// getters

	std::string getName();
	int getScore();
	sf::Text* getrefNameTextbox();
	sf::Text* getrefScoreTextbox();

	// setters

	void setName(std::string name);
	void setScore(int score);

	// textbox functions

	void updateNameTextboxString();
	void updateScoreTextboxString();
};

