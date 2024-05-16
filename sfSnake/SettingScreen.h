#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H

#include <SFML/Graphics.hpp>

#include "Screen.h"
#include "Button.h"

namespace sfSnake
{
	class SettingScreen : public Screen
	{
	public:
		SettingScreen();

		void handleInput(sf::RenderWindow& window) override;
		void update(sf::Time delta) override;
		void render(sf::RenderWindow& window) override;

		bool goBack(sf::RenderWindow& window);

		void toggleBgDropdown(sf::RenderWindow& window);
		void toggleGridDropdown(sf::RenderWindow& window);

		static sf::Color getBgColor();
		static sf::Color getGridColor();

	private:
		static sf::Color bgColor_;
		static sf::Color gridColor_;

		sf::Font font_;

		Button exitButton_;

		Button currentBgColorButton_;
		Button currentGridColorButton_;

		Button setBgColorButton_;
		Button setGridColorButton_;

		Button gridColorBlackButton_;
		Button gridColorBrownButton_;
		Button gridColorWhiteButton_;

		Button bgColorBlackButton_;
		Button bgColorBrownButton_; 
		Button bgColorWhiteButton_;

		Button gridEnableButton_;
	};
}

#endif