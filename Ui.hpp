#pragma once
#include <SFML/Graphics.hpp>

class Ui {
private:
	static bool m_fade_animation_lock;
	static void TriggerFadeOutAnimation(sf::Text* text);

public:
	sf::Font m_font;

	Ui();

	static void FadeOut(sf::Text* text);
	sf::Text* MakeText(const sf::Color& text_color, unsigned int char_size, const std::string& string);
};