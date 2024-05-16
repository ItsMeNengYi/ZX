#include <SFML/Graphics.hpp>

#include "Button.h"
#include "Game.h"


using namespace sfSnake;

Button::Button()
	: bindKey_(sf::Keyboard::Key()),
	visible_(true),
	hasBackgroundColor_(false),
	hoverAnim_(HoverAnimation::None)
{
}

Button::Button(sf::String text, sf::Vector2f position)
	: bindKey_(sf::Keyboard::Key()),
	visible_(true),
	hasBackgroundColor_(false),
	hoverAnim_(HoverAnimation::None)
{
	position_ = position;
	this->setString(text);
	this->setPosition(position);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (visible_) 
	{
		if (hasBackgroundColor_)
			target.draw(backgroundRect_, states);

		switch (hoverAnim_)
		{
		case HoverAnimation::backgroundLightUp:
			if (sf::RenderWindow* windowPtr = dynamic_cast<sf::RenderWindow*>(&target)) {
				if (isHoveredOver(*windowPtr)) 
				{
					hasBackgroundColor_ = true;
				}
				else 
				{
					hasBackgroundColor_ = false;
				}
			}
			break;

		default :
			break;
		}
			
		target.draw((sf::Text)*this, states);
	}
}
	

void Button::bindKey(sf::Keyboard::Key key)
{
	bindKey_ = key;
}

bool Button::isClicked(sf::RenderWindow& window)
{
	return visible_ && sf::Keyboard::isKeyPressed(bindKey_) || sf::Mouse::isButtonPressed(sf::Mouse::Left) && isHoveredOver(window);
}

bool Button::isHoveredOver(sf::RenderWindow& window) const
{
	auto mousePosition = sf::Mouse::getPosition(window);
	sf::FloatRect textBounds = this->getGlobalBounds();

	bool insideX = mousePosition.x >= textBounds.left && mousePosition.x <= textBounds.left + textBounds.width;
	bool insideY = mousePosition.y >= textBounds.top && mousePosition.y <= textBounds.top + textBounds.height;
	return visible_ && insideX && insideY;
}

void Button::setPositionUnderButton(Button button, float align)
{
	sf::FloatRect bounds = button.getLocalBounds();
	sf::Vector2f position = button.getPosition();

	this->setPosition(position.x, position.y + 2 * bounds.height);
	this->move((align - 0.5) * (bounds.width - this->getLocalBounds().width), 0);

}

void Button::setOriginToMiddle() 
{
	sf::FloatRect textBounds = this->getLocalBounds();
	this->setOrigin(textBounds.left + textBounds.width / 2,
		textBounds.top + textBounds.height / 2);
}

void Button::setBackgroundColor(sf::Color color)
{
	hasBackgroundColor_ = true;
	backgroundRect_.setSize(sf::Vector2f(this->getWidth(), this->getHeight()));
	backgroundRect_.setFillColor(color);
	sf::FloatRect rectBounds = backgroundRect_.getLocalBounds();
	backgroundRect_.setOrigin(rectBounds.left + rectBounds.width / 2,
		rectBounds.top + rectBounds.height / 2);
	backgroundRect_.setPosition(this->getPosition());
}

void Button::setHoverAnimation(Button::HoverAnimation anim)
{
	this->hoverAnim_ = anim;
}

sf::Color Button::getBgColor()
{
	return backgroundRect_.getFillColor();
}

float Button::getWidth()
{
	return this->getLocalBounds().width;
}

float Button::getHeight()
{
	return this->getLocalBounds().height;
}

void Button::setInvisible()
{
	visible_ = false;
}

void Button::setVisible()
{
	visible_ = true;
}

void Button::toggleVisibility()
{
	visible_ = !visible_;
}

void Button::copyFrom(Button button)
{
	this->setString(button.getString());
	this->setBackgroundColor(button.backgroundRect_.getFillColor());
}

