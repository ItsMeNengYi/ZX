#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Snake.h"
#include "Fruit.h"

namespace sfSnake
{
class GameScreen : public Screen
{
public:
	GameScreen();

	void handleInput(sf::RenderWindow& window) override;
	void update(sf::Time delta) override;
	void render(sf::RenderWindow& window) override;

	void generateFruit();

private:
	void drawGrid(sf::RenderWindow& window);
	void drawBackground(sf::RenderWindow& window);

private:
	Snake snake_;
	std::vector<Fruit> fruit_;

	sf::Color gridColor_ = sf::Color::Black;
	sf::Color bgColor_ = sf::Color::White;

};
}

#endif