#include <SFML/Graphics.hpp>

#include <memory>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"

using namespace sfSnake;

MenuScreen::MenuScreen()
	:startButton_("Play [Space]"),
	exitButton_("Exit [Esc]"),
	settingButton_("Setting [S]")
{
	font_.loadFromFile("Fonts/game_over.ttf");
	startButton_.setFont(font_);
	settingButton_.setFont(font_);
	exitButton_.setFont(font_);

	startButton_.setOriginToMiddle();
	settingButton_.setOriginToMiddle();
	exitButton_.setOriginToMiddle();

	startButton_.bindKey(sf::Keyboard::Space);
	settingButton_.bindKey(sf::Keyboard::S);
	exitButton_.bindKey(sf::Keyboard::Escape);

	startButton_.setPosition(sf::Vector2f(Game::Width / 2, Game::Height / 2));
	settingButton_.setPositionUnderButton(startButton_, 0.5);
	exitButton_.setPositionUnderButton(settingButton_, 0.5);

	startButton_.setBackgroundColor(sf::Color::Green);
	settingButton_.setBackgroundColor(sf::Color::Green);
	exitButton_.setBackgroundColor(sf::Color::Green);

	startButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);
	settingButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);
	exitButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);


	snakeText_.setFont(font_);
	snakeText_.setString("Snake!");
	snakeText_.setFillColor(sf::Color::Green);
	snakeText_.setCharacterSize(64);
	snakeText_.setStyle(sf::Text::Bold);

	sf::FloatRect snakeTextBounds = snakeText_.getLocalBounds();
	snakeText_.setOrigin(snakeTextBounds.left + snakeTextBounds.width / 2,
		snakeTextBounds.top + snakeTextBounds.height / 2);
	snakeText_.setPosition(Game::Width / 2, Game::Height / 4);
}

void MenuScreen::handleInput(sf::RenderWindow& window)
{
	if (goToSetting(window))
		Game::Screen = std::make_shared<SettingScreen>();
	else if (startGame(window))
		Game::Screen = std::make_shared<GameScreen>();
	else if (exitButton_.isClicked(window))
		window.close();
}

void MenuScreen::update(sf::Time delta)
{
	static bool movingLeft = false;
	static bool movingRight = true;

	if (movingRight)
	{
		snakeText_.rotate(delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == 10)
		{
			movingRight = false;
			movingLeft = true;
		}
	}

	if (movingLeft)
	{
		snakeText_.rotate(-delta.asSeconds());

		if (static_cast<int>(snakeText_.getRotation()) == (360 - 10))
		{
			movingLeft = false;
			movingRight = true;
		}
	}
}

void MenuScreen::render(sf::RenderWindow& window)
{

	window.draw(startButton_);
	window.draw(settingButton_);
	window.draw(exitButton_);

	window.draw(snakeText_);
}

bool MenuScreen::goToSetting(sf::RenderWindow& window)
{
	return settingButton_.isClicked(window);
}

bool MenuScreen::startGame(sf::RenderWindow& window)
{
	return startButton_.isClicked(window);
}
