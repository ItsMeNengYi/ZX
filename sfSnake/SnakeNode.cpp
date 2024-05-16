#include <SFML/Graphics.hpp>
#include <iostream>

#include "SnakeNode.h"

using namespace sfSnake;

const float SnakeNode::Width = 20.f;
const float SnakeNode::Height = 20.f;

SnakeNode::SnakeNode(sf::Texture& texture, sf::Vector2f position)
: position_(position)
{
	shape_.setFillColor(sf::Color::Green);
	shape_.setSize(sf::Vector2f(SnakeNode::Width, SnakeNode::Height));
	shape_.setOutlineColor(sf::Color::White);
	shape_.setOutlineThickness(-1.f);

	sprite_.setTexture(texture);
	scale_ = 2 * SnakeNode::Width / texture.getSize().x;
	sprite_.setScale(scale_, scale_);

	setAllPosition();

}

void SnakeNode::setPosition(sf::Vector2f position)
{
	position_ = position;
	setAllPosition();

}

void SnakeNode::setPosition(float x, float y)
{
	position_.x = x;
	position_.y = y;
	setAllPosition();
}

void SnakeNode::move(float xOffset, float yOffset)
{
	position_.x += xOffset;
	position_.y += yOffset;
	setAllPosition();
}

sf::FloatRect SnakeNode::getBounds() const
{
	return shape_.getGlobalBounds();
}

sf::FloatRect SnakeNode::getSpriteBounds() const
{
	return sprite_.getGlobalBounds();
}

sf::Vector2f SnakeNode::getPosition() const
{
	return position_;
}

void SnakeNode::render(sf::RenderWindow& window)
{
	window.draw(sprite_);
}

void SnakeNode::setAllPosition()
{

	prevPosition_ = shape_.getPosition();
	shape_.setPosition(position_);

	sf::FloatRect shapeBounds = shape_.getLocalBounds();
	sf::FloatRect spriteBounds = sprite_.getLocalBounds();
	sprite_.setOrigin(spriteBounds.left + spriteBounds.width / 2, spriteBounds.top + spriteBounds.width / 2);
	sprite_.setPosition(position_.x + shapeBounds.width/2 , position_.y + shapeBounds.width/2);

	float delX = position_.x - prevPosition_.x;
	float delY = position_.y - prevPosition_.y;
	float displacement = sqrt(delX * delX + delY * delY);
	float angle = 0;
	if (delX == 0) 
	{
		if (delY > 0) 
		{
			angle = 180;
		}
		else 
		{
			angle = 0;
		}
	}
	else
	{
		angle = atan(delY / delX) / 3.14 * 180 + 90;
		if (prevPosition_.x > position_.x)
		{
			angle += 180;
		}
	}
	if (displacement > SnakeNode::Width)
	{
		angle = prevAngle_;
	}
	sprite_.setRotation(round(angle));
	prevAngle_ = angle;
}