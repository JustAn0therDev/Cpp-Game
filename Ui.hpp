#pragma once
#include <SFML/Graphics.hpp>

class Ui {
public:
	sf::Font m_font;
	static bool m_is_running_fade_animation;

	Ui();

	static void FadeOut(sf::Text *text);
	sf::Text* MakeText(const sf::Color& text_color, unsigned int char_size, const std::string& string);
};