#pragma once
#include <SFML/Graphics.hpp>

class Ui {
public:
	sf::Font m_font;

	Ui();

	static void FadeOut(sf::Text *text);
	sf::Text* CreateText();
};