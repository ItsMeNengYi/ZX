#ifndef GAME_OVER_SCREEN_H
#define GAME_OVER_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "MenuScreen.h"
#include "SettingScreen.h"
#include "Button.h"

namespace sfSnake
{
class GameOverScreen : public Screen
{
public:
	GameOverScreen(std::size_t score);

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

private:
	sf::Font font_;
	sf::Text text_;

	unsigned score_;

	Button retryButton_;
	Button menuButton_;
};
}

#endif