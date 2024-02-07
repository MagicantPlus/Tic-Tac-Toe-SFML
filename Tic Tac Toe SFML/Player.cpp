#include "Player.h"

Player::Player()
{
	this->initVariables();
}

Player::~Player()
{

}

// initializers

void Player::initVariables()
{
	this->textFont.loadFromFile("Arialn.ttf");
	this->setScore(0);

	this->initNameTextbox();
	this->initScoreTextbox();
}

void Player::initNameTextbox()
{
	this->nameTextbox.setCharacterSize(this->TEXTBOX_CHARACTER_SIZE);
	this->nameTextbox.setFillColor(sf::Color(0, 0, 0, 255));
	this->nameTextbox.setFont(this->textFont);
}

void Player::initScoreTextbox()
{
	this->scoreTextbox.setCharacterSize(this->TEXTBOX_CHARACTER_SIZE);
	this->scoreTextbox.setFillColor(sf::Color(0, 0, 0, 255));
	this->scoreTextbox.setFont(this->textFont);
}

// getters

std::string Player::getName()
{
	return this->name;
}

int Player::getScore()
{
	return this->score;
}

sf::Text* Player::getrefNameTextbox()
{
	return &this->nameTextbox;
}

sf::Text* Player::getrefScoreTextbox()
{
	return &this->scoreTextbox;
}

// setters

void Player::setName(std::string name)
{
	this->name = name;
	this->updateNameTextboxString();
}

void Player::setScore(int score)
{
	this->score = score;
	this->updateScoreTextboxString();
}

// textbox functions

void Player::updateNameTextboxString()
{
	this->nameTextbox.setString(this->name + " SCORE");
}

void Player::updateScoreTextboxString()
{
	std::string scoreString = "";
	int tempScore = this->score;

	if (tempScore == 0)
	{
		scoreString = "0";
	}
	else
	{
		while (tempScore > 0)
		{
			scoreString += (char)(tempScore % 10 + '0');
			tempScore /= 10;
		}
	}

	for (int i = 0, j = scoreString.size() - 1; i < j; i++, j--)
	{
		std::swap(scoreString[i], scoreString[j]);
	}

	this->scoreTextbox.setString(scoreString);
}