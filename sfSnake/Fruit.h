#ifndef FRUIT_H
#define FRUIT_H

#include <SFML/Graphics.hpp>

#define BLACK_LEN 0
#define BROWN_LEN 0
#define RED_LEN 3
#define BLUE_LEN 2
#define GREEN_LEN 1

#define BLACK sf::Color::Black
#define BROWN sf::Color::Color(92, 64, 51)
#define RED sf::Color::Red
#define BLUE sf::Color::Blue
#define GREEN sf::Color::Green

namespace sfSnake
{
class Fruit
{
public:
	Fruit(sf::Vector2f position = sf::Vector2f(0, 0));

	void render(sf::RenderWindow& window);

	sf::FloatRect getBounds() const;

	uint16_t getIncLen() const;

private:
	sf::CircleShape shape_;

	uint16_t index_;
	uint16_t lens[5] = {BLACK_LEN, BROWN_LEN, RED_LEN, BLUE_LEN, GREEN_LEN};
	sf::Color colors[5] = { BLACK, BROWN, RED, BLUE, GREEN };

	static const float Radius;
};
}

#endif