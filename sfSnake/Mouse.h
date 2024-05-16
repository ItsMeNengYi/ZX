#ifndef MOUSE_H
#define MOUSE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>

namespace sfSnake
{
	class Mouse
	{
	public:
		Mouse();

		static sf::Vector2f getMoveDirection(sf::Vector2f snakePos);

		static bool ButtonIsPressed(sf::RenderWindow& window);
	private:
		static sf::Vector2i currentMousePos_;
	};
}


#endif