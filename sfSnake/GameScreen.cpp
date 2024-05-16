#include <SFML/Graphics.hpp>

#include <random>
#include <memory>

#include "GameScreen.h"
#include "GameOverScreen.h"
#include "SettingScreen.h"
#include "Game.h"

using namespace sfSnake;


GameScreen::GameScreen() : snake_()
{
	gridColor_ = SettingScreen::getGridColor();
	bgColor_ = SettingScreen::getBgColor();
}

void GameScreen::handleInput(sf::RenderWindow& window)
{
	snake_.handleInput(window);
}

void GameScreen::update(sf::Time delta)
{
	if (fruit_.size() == 0)
		generateFruit();

	snake_.update(delta);
	snake_.checkFruitCollisions(fruit_);

	if (snake_.hitSelf())
		Game::Screen = std::make_shared<GameOverScreen>(snake_.getSize());
}

void GameScreen::render(sf::RenderWindow& window)
{
	drawBackground(window);
	drawGrid(window);
	snake_.render(window);

	for (auto fruit : fruit_)
		fruit.render(window);
}

void GameScreen::generateFruit()
{
	static std::default_random_engine engine;
	engine.seed(time(NULL));
	static std::uniform_int_distribution<int> xDistribution(0, Game::Width -  SnakeNode::Width);
	static std::uniform_int_distribution<int> yDistribution(0, Game::Height - SnakeNode::Height);

	fruit_.push_back(Fruit(sf::Vector2f(xDistribution(engine), yDistribution(engine))));
}



void GameScreen::drawGrid(sf::RenderWindow& window)
{
	sf::VertexArray line(sf::LinesStrip, 2);

	// Column
	for (int i = SnakeNode::Width; i < Game::Width; i += SnakeNode::Width)
	{
		line[0].position = sf::Vector2f(i, 0);
		line[1].position = sf::Vector2f(i, Game::Height);
		line[0].color = gridColor_;
		line[1].color = gridColor_;
		window.draw(line);
	}

	// Column
	for (int i = SnakeNode::Height; i < Game::Height; i += SnakeNode::Height)
	{
		line[0].position = sf::Vector2f(0, i);
		line[1].position = sf::Vector2f(Game::Width, i);
		line[0].color = gridColor_;
		line[1].color = gridColor_;
		window.draw(line);
	}
}

void GameScreen::drawBackground(sf::RenderWindow& window)
{
	sf::RectangleShape bg(sf::Vector2f(Game::Width, Game::Height));
	bg.setFillColor(bgColor_);
	window.draw(bg);
}

