#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "GameScreen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Game.h"

#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define BROWN sf::Color(92, 64, 51)

using namespace sfSnake;

sf::Color SettingScreen::bgColor_ = WHITE;
sf::Color SettingScreen::gridColor_ = BLACK;

SettingScreen::SettingScreen()
	:exitButton_("Back [Esc]"),
	currentBgColorButton_("White"),
	currentGridColorButton_("Black"),
	setBgColorButton_("Background Color: "),
	setGridColorButton_("Grid Color: "),
	gridColorBlackButton_("Black"),
	gridColorBrownButton_("Brown"),
	gridColorWhiteButton_("White"),
	bgColorBlackButton_("Black"),
	bgColorBrownButton_("Brown"),
	bgColorWhiteButton_("White"),
	gridEnableButton_("Enabled")
{
	font_.loadFromFile("Fonts/game_over.ttf");
	exitButton_.setFont(font_);
	currentBgColorButton_.setFont(font_);
	currentGridColorButton_.setFont(font_);
	setBgColorButton_.setFont(font_);
	setGridColorButton_.setFont(font_);
	gridColorBlackButton_.setFont(font_);
	gridColorBrownButton_.setFont(font_);
	gridColorWhiteButton_.setFont(font_);
	bgColorBlackButton_.setFont(font_);
	bgColorBrownButton_.setFont(font_);
	bgColorWhiteButton_.setFont(font_);
	gridEnableButton_.setFont(font_);

	currentBgColorButton_.setOriginToMiddle();
	currentGridColorButton_.setOriginToMiddle();
	setBgColorButton_.setOriginToMiddle();
	setGridColorButton_.setOriginToMiddle();
	gridColorBlackButton_.setOriginToMiddle();
	gridColorBrownButton_.setOriginToMiddle();
	gridColorWhiteButton_.setOriginToMiddle();
	bgColorBlackButton_.setOriginToMiddle();
	bgColorBrownButton_.setOriginToMiddle();
	bgColorWhiteButton_.setOriginToMiddle();
	gridEnableButton_.setOriginToMiddle();

	exitButton_.bindKey(sf::Keyboard::Escape);

	currentBgColorButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);
	currentGridColorButton_.setHoverAnimation(Button::HoverAnimation::backgroundLightUp);

	setBgColorButton_.setPosition(Game::Width / 2 + setBgColorButton_.getWidth() / 4,
		Game::Height / 2 - setBgColorButton_.getHeight()/2);
	setGridColorButton_.setPositionUnderButton(setBgColorButton_, 0);
	gridEnableButton_.setPositionUnderButton(setGridColorButton_, 1);

	currentBgColorButton_.setPosition(Game::Width / 2 + setBgColorButton_.getWidth(),
		Game::Height / 2 - currentBgColorButton_.getHeight() / 2);
	currentGridColorButton_.setPositionUnderButton(currentBgColorButton_, 0);

	gridColorBlackButton_.setPositionUnderButton(currentGridColorButton_, 0);
	gridColorBrownButton_.setPositionUnderButton(gridColorBlackButton_, 0);
	gridColorWhiteButton_.setPositionUnderButton(gridColorBrownButton_, 0);
	bgColorBlackButton_.setPositionUnderButton(currentBgColorButton_, 0);
	bgColorBrownButton_.setPositionUnderButton(bgColorBlackButton_, 0);
	bgColorWhiteButton_.setPositionUnderButton(bgColorBrownButton_, 0);

	bgColorBlackButton_.setFillColor(WHITE);
	bgColorBrownButton_.setFillColor(WHITE);
	bgColorWhiteButton_.setFillColor(BLACK);
	gridColorBlackButton_.setFillColor(WHITE);
	gridColorBrownButton_.setFillColor(WHITE);
	gridColorWhiteButton_.setFillColor(BLACK);

	gridColorBlackButton_.setBackgroundColor(BLACK);
	gridColorBrownButton_.setBackgroundColor(BROWN);
	gridColorWhiteButton_.setBackgroundColor(WHITE);
	bgColorBlackButton_.setBackgroundColor(BLACK);
	bgColorBrownButton_.setBackgroundColor(BROWN);
	bgColorWhiteButton_.setBackgroundColor(WHITE);

	gridEnableButton_.setBackgroundColor(sf::Color::Green);

	gridColorBlackButton_.setInvisible();
	gridColorBrownButton_.setInvisible();
	gridColorWhiteButton_.setInvisible();
	bgColorBlackButton_.setInvisible();
	bgColorBrownButton_.setInvisible();
	bgColorWhiteButton_.setInvisible();
}

void SettingScreen::handleInput(sf::RenderWindow& window)
{
	if (gridColorBlackButton_.isClicked(window)) 
	{
		currentGridColorButton_.copyFrom(gridColorBlackButton_);
	}
	if (gridColorBrownButton_.isClicked(window))
	{
		currentGridColorButton_.copyFrom(gridColorBrownButton_);
	}
	if (gridColorWhiteButton_.isClicked(window))
	{
		currentGridColorButton_.copyFrom(gridColorWhiteButton_);
	}
	if (bgColorBlackButton_.isClicked(window))
	{
		currentBgColorButton_.copyFrom(bgColorBlackButton_);
	}
	if (bgColorBrownButton_.isClicked(window))
	{
		currentBgColorButton_.copyFrom(bgColorBrownButton_);
	}
	if (bgColorWhiteButton_.isClicked(window))
	{
		currentBgColorButton_.copyFrom(bgColorWhiteButton_);
	}
	toggleBgDropdown(window);
	toggleGridDropdown(window);

	if (gridEnableButton_.isClicked(window))
	{
		if (gridEnableButton_.getString().toAnsiString() == "Enabled")
		{
			gridEnableButton_.setString("Disabled");
			gridEnableButton_.setBackgroundColor(sf::Color::Red);
		}
		else
		{
			gridEnableButton_.setString("Enabled");
			gridEnableButton_.setBackgroundColor(sf::Color::Green);
		}
	}

	if (goBack(window))
	{
		if (gridEnableButton_.getString().toAnsiString() == "Enabled")
		{
			gridColor_ = currentGridColorButton_.getBgColor();
		}
		else
		{
			gridColor_ = currentBgColorButton_.getBgColor();
		}
		bgColor_ = currentBgColorButton_.getBgColor();
		Game::Screen = std::make_shared<MenuScreen>();
	}
}

void SettingScreen::update(sf::Time delta)
{

}

void SettingScreen::render(sf::RenderWindow& window)
{
	window.draw(exitButton_);
	window.draw(currentBgColorButton_);
	window.draw(currentGridColorButton_);
	window.draw(setBgColorButton_);
	window.draw(setGridColorButton_);
	window.draw(gridColorBlackButton_);
	window.draw(gridColorBrownButton_);
	window.draw(gridColorWhiteButton_);
	window.draw(bgColorBlackButton_);
	window.draw(bgColorBrownButton_);
	window.draw(bgColorWhiteButton_);
	window.draw(gridEnableButton_);
}

bool SettingScreen::goBack(sf::RenderWindow& window)
{
	return exitButton_.isClicked(window);
}

void SettingScreen::toggleBgDropdown(sf::RenderWindow& window)
{
	if (currentBgColorButton_.isHoveredOver(window) ||
		bgColorBlackButton_.isHoveredOver(window) ||
		bgColorBrownButton_.isHoveredOver(window) ||
		bgColorWhiteButton_.isHoveredOver(window))
	{
		bgColorBlackButton_.setVisible();
		bgColorBrownButton_.setVisible();
		bgColorWhiteButton_.setVisible();
		gridColorBlackButton_.setInvisible();
		gridColorBrownButton_.setInvisible();
		gridColorWhiteButton_.setInvisible(); 
		currentGridColorButton_.setInvisible();
	} 
	if (currentBgColorButton_.isClicked(window) ||
		bgColorBlackButton_.isClicked(window) ||
		bgColorBrownButton_.isClicked(window) ||
		bgColorWhiteButton_.isClicked(window))
	{
		bgColorBlackButton_.setInvisible();
		bgColorBrownButton_.setInvisible();
		bgColorWhiteButton_.setInvisible();
		currentGridColorButton_.setVisible();
	}
}

void SettingScreen::toggleGridDropdown(sf::RenderWindow& window)
{
	if (currentGridColorButton_.isHoveredOver(window) ||
		gridColorBlackButton_.isHoveredOver(window) ||
		gridColorBrownButton_.isHoveredOver(window) ||
		gridColorWhiteButton_.isHoveredOver(window))
	{
		gridColorBlackButton_.setVisible();
		gridColorBrownButton_.setVisible();
		gridColorWhiteButton_.setVisible();
		bgColorBlackButton_.setInvisible();
		bgColorBrownButton_.setInvisible();
		bgColorWhiteButton_.setInvisible();
	}
	if (currentGridColorButton_.isClicked(window) ||
		gridColorBlackButton_.isClicked(window) ||
		gridColorBrownButton_.isClicked(window) ||
		gridColorWhiteButton_.isClicked(window))
	{
		gridColorBlackButton_.setInvisible();
		gridColorBrownButton_.setInvisible();
		gridColorWhiteButton_.setInvisible();
	}
}

sf::Color SettingScreen::getBgColor()
{
	return bgColor_;
}

sf::Color SettingScreen::getGridColor()
{
	return gridColor_;
}
