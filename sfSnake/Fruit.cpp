#include <SFML/Graphics.hpp>


#include "Fruit.h"

using namespace sfSnake;

const float Fruit::Radius = 10.f;

Fruit::Fruit(sf::Vector2f position)
{
	int i = rand() % 4;
	if (i == 0)
	{
		index_ = rand() % 2;
	}
	else
	{
		index_ = i + 1;
	}

	shape_.setPosition(position);
	shape_.setRadius(Fruit::Radius);
	shape_.setFillColor(colors[index_]);
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(-1.f);
}

void Fruit::render(sf::RenderWindow& window)
{
	window.draw(shape_);
}

sf::FloatRect Fruit::getBounds() const
{
	return shape_.getGlobalBounds();
}

uint16_t sfSnake::Fruit::getIncLen() const
{
	return lens[index_];
}
