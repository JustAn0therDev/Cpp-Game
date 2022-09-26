#pragma once
#include <SFML/Graphics.hpp>

class Ui {
public:
	static void FadeOut(sf::Text& text);
	static void InitializeRestartingText(sf::Text& text, const sf::Font& font);
};