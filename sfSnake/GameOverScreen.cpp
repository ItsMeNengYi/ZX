#include <SFML/Graphics.hpp>

#include <iostream>
#include <memory>

#include "Game.h"
#include "GameScreen.h"
#include "GameOverScreen.h"

using namespace sfSnake;

GameOverScreen::GameOverScreen(std::size_t score) 
	: score_(score),
	retryButton_("retry [SPACE]"),
	menuButton_("menu [ESC]")
{
	font_.loadFromFile("Fonts/game_over.ttf");
	text_.setFont(font_);
	text_.setString("Your score: " + std::to_string(score) + "!");
	text_.setFillColor(sf::Color::Red);

	sf::FloatRect textBounds = text_.getLocalBounds();
	text_.setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
	text_.setPosition(Game::Width / 2, Game::Height / 3);

	retryButton_.setFont(font_);
	retryButton_.setOriginToMiddle();
	retryButton_.setPosition(Game::Width / 2, Game::Height / 2);
	retryButton_.setBackgroundColor(sf::Color::Red);
	retryButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);

	menuButton_.setFont(font_);
	menuButton_.setOriginToMiddle();
	menuButton_.setPositionUnderButton(retryButton_, 0.5);
	menuButton_.setBackgroundColor(sf::Color::Red);
	menuButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);
}

void GameOverScreen::handleInput(sf::RenderWindow& window)
{
	if (retryButton_.isClicked(window))
		Game::Screen = std::make_shared<GameScreen>();
	else if (menuButton_.isClicked(window))
		Game::Screen = std::make_shared<MenuScreen>();
}

void GameOverScreen::update(sf::Time delta)
{

}

void GameOverScreen::render(sf::RenderWindow& window)
{
	window.draw(text_);

	window.draw(retryButton_);
	window.draw(menuButton_);
}