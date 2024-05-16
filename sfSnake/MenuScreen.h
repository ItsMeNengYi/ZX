#ifndef MENU_SCREEN_H
#define MENU_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
class MenuScreen : public Screen
{
public:
	MenuScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	bool goToSetting(sf::RenderWindow& window);
	bool startGame(sf::RenderWindow& window);

private:
	sf::Font font_;
	sf::Text snakeText_;

	sf::Text startText_;
	sf::Text exitText_;
	sf::Text settingText_;

	Button startButton_;
	Button exitButton_;
	Button settingButton_;
};
}

#endif