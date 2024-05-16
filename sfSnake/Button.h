#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>

#include "Screen.h"

namespace sfSnake
{
class Button : public sf::Text
{
public:
	enum class HoverAnimation
	{
		backgroundLightUp, None
	};
public:
	Button();
	Button(sf::String text, 
		sf::Vector2f position = sf::Vector2f(0.0f, 0.0f));

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void bindKey(sf::Keyboard::Key key);

	bool isClicked(sf::RenderWindow& window);
	bool isHoveredOver(sf::RenderWindow& window) const;

	void setPositionUnderButton(Button button, float align);
	
	void setOriginToMiddle();

	void setBackgroundColor(sf::Color color);

	void setHoverAnimation(Button::HoverAnimation anim);

	sf::Color getBgColor();

	float getWidth();
	float getHeight();

	void setInvisible();
	void setVisible();
	void toggleVisibility();

	void copyFrom(Button button);

private:
	sf::Vector2f position_;

	bool visible_;
	mutable bool hasBackgroundColor_;

	HoverAnimation hoverAnim_;

	sf::RectangleShape backgroundRect_;

	sf::Keyboard::Key bindKey_;
};
}

#endif