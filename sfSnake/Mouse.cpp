#include <SFML/Window/Mouse.hpp>

#include <iostream>

#include "Mouse.h"
#include "Screen.h"

using namespace sfSnake;

sf::Vector2i Mouse::currentMousePos_ = sf::Vector2i(0, 0);

Mouse::Mouse()
{

}

bool Mouse::ButtonIsPressed(sf::RenderWindow& window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i temp = sf::Mouse::getPosition(window);
		if (temp.x >= 0 && temp.y >= 0 && (temp.x == 0 || temp.y != 0))
		{
			currentMousePos_ = temp;
			return true;
		}
	}
	return false;
}

sf::Vector2f Mouse::getMoveDirection(sf::Vector2f snakePos)
{
	float delX = currentMousePos_.x - snakePos.x;
	float delY = currentMousePos_.y - snakePos.y;
	float dist = sqrt(delX * delX + delY * delY);
	return sf::Vector2f(delX / dist, delY / dist);
}