#include <SFML/Graphics.hpp>

#include <memory>
#include <iostream>

#include "Snake.h"
#include "Game.h"
#include "Fruit.h"
#include "SnakeNode.h"
#include "GameOverScreen.h"
#include "Mouse.h"

using namespace sfSnake;

const int Snake::InitialSize = 5;

Snake::Snake() : direction_(Direction::Up), hitSelf_(false), mouseControl_(false)
{
	pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
	pickupSound_.setBuffer(pickupBuffer_);
	pickupSound_.setVolume(30);

	dieBuffer_.loadFromFile("Sounds/die.wav");
	dieSound_.setBuffer(dieBuffer_);
	dieSound_.setVolume(50);

	headTexture_.loadFromFile("Picture/Snake/snakeHead.jpg");
	bodyTexture_.loadFromFile("Picture/Snake/snakeBody.jpg");

	initNodes();

}

void Snake::initNodes()
{
	for (int i = 0; i < Snake::InitialSize; ++i)
	{
		sf::Sprite tempSprite;
		// Sprites
		if (i == 0) 
		{
			nodes_.push_back(SnakeNode(headTexture_, sf::Vector2f(
				Game::Width / 2 - SnakeNode::Width / 2,
				Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
		} 
		else
		{
			nodes_.push_back(SnakeNode(bodyTexture_, sf::Vector2f(
				Game::Width / 2 - SnakeNode::Width / 2,
				Game::Height / 2 - (SnakeNode::Height / 2) + (SnakeNode::Height * i))));
		}
		
	}
}

void Snake::handleInput(sf::RenderWindow& window)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		mouseControl_ = false;
		direction_ = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		mouseControl_ = false;
		direction_ = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		mouseControl_ = false;
		direction_ = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		mouseControl_ = false;
		direction_ = Direction::Right;
	}

	if (Mouse::ButtonIsPressed(window)) {
		mouseControl_ = true;
		mouseDirection_ = Mouse::getMoveDirection(nodes_[0].getPosition());
	}
}

void Snake::update(sf::Time delta)
{
	move();
	checkEdgeCollisions();
	checkSelfCollisions();
}

void Snake::checkFruitCollisions(std::vector<Fruit>& fruits)
{
	auto toRemove = fruits.end();

	for (auto it = fruits.begin(); it != fruits.end(); ++it)
	{
		if (it->getBounds().intersects(nodes_[0].getSpriteBounds()))
			toRemove = it;
	}

	if (toRemove != fruits.end())
	{
		pickupSound_.play();
		for (int i = 0; i < toRemove->getIncLen(); i++) 
		{
			grow();
		}
		fruits.erase(toRemove);
	}
}

void Snake::grow()
{
	if (mouseControl_) {
		nodes_.push_back(SnakeNode(bodyTexture_, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - mouseDirection_.x * SnakeNode::Width,
			nodes_[nodes_.size() - 1].getPosition().y - mouseDirection_.y * SnakeNode::Height)));
	}
	else
	{
		switch (direction_)
		{
		case Direction::Up:
			nodes_.push_back(SnakeNode(bodyTexture_, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y + SnakeNode::Height)));
			break;
		case Direction::Down:
			nodes_.push_back(SnakeNode(bodyTexture_, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x,
				nodes_[nodes_.size() - 1].getPosition().y - SnakeNode::Height)));
			break;
		case Direction::Left:
			nodes_.push_back(SnakeNode(bodyTexture_, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x + SnakeNode::Width,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		case Direction::Right:
			nodes_.push_back(SnakeNode(bodyTexture_, sf::Vector2f(nodes_[nodes_.size() - 1].getPosition().x - SnakeNode::Width,
				nodes_[nodes_.size() - 1].getPosition().y)));
			break;
		}
	}
}

unsigned Snake::getSize() const
{
	return nodes_.size();
}

bool Snake::hitSelf() const
{
	return hitSelf_;
}

void Snake::checkSelfCollisions()
{
	SnakeNode& headNode = nodes_[0];

	for (decltype(nodes_.size()) i = 2; i < nodes_.size(); ++i)
	{
		if (headNode.getBounds().intersects(nodes_[i].getBounds()))
		{
			dieSound_.play();
			sf::sleep(sf::seconds(dieBuffer_.getDuration().asSeconds()));
			hitSelf_ = true;
		}
	}
}

void Snake::checkEdgeCollisions()
{
	SnakeNode& headNode = nodes_[0];

	if (headNode.getPosition().x <= 0)
		headNode.setPosition(Game::Width, headNode.getPosition().y);
	else if (headNode.getPosition().x >= Game::Width)
		headNode.setPosition(0, headNode.getPosition().y);
	else if (headNode.getPosition().y <= 0)
		headNode.setPosition(headNode.getPosition().x, Game::Height);
	else if (headNode.getPosition().y >= Game::Height)
		headNode.setPosition(headNode.getPosition().x, 0);
}

void Snake::move()
{
	for (decltype(nodes_.size()) i = nodes_.size() - 1; i > 0; --i)
	{
		nodes_[i].setPosition(nodes_.at(i - 1).getPosition());
	}
	if (mouseControl_)
	{
		//std::cout << mouseDirection_.x << " " << mouseDirection_.y<<std::endl;
		nodes_[0].move(mouseDirection_.x * SnakeNode::Width, mouseDirection_.y * SnakeNode::Height);
	}
	else
	{
		switch (direction_)
		{
		case Direction::Up:
			nodes_[0].move(0, -SnakeNode::Height);
			break;
		case Direction::Down:
			nodes_[0].move(0, SnakeNode::Height);
			break;
		case Direction::Left:
			nodes_[0].move(-SnakeNode::Width, 0);
			break;
		case Direction::Right:
			nodes_[0].move(SnakeNode::Width, 0);
			break;
		}
	}
}

void Snake::render(sf::RenderWindow& window)
{
	for (int i = nodes_.size() - 1; i >= 0; i--) 
	{
		nodes_[i].render(window);
	}
}