#pragma once
#include "Ui.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include <thread>
#include "Constants.hpp"
#include <memory>
#include <iostream>

Ui::Ui() : m_font(sf::Font()) {
	if (!m_font.loadFromFile(FONT_PATH)) {
		std::cout << "Could not open font file.\n";
		exit(1);
	}
}

void Ui::FadeOut(sf::Text* text) {
	if (!g_is_running_fade_animation) {
		g_is_running_fade_animation = true;

		sf::Color color = sf::Color::White;

		while (color.a > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			color.a -= 1;
			text->setFillColor(color);
		}

		g_is_running_fade_animation = false;
	}
}

sf::Text* Ui::CreateText() {
	sf::Text* text = new sf::Text;
	text->setFont(m_font);
	text->setFillColor(DEFAULT_TRANSPARENT_WHITE_COLOR);
	text->setCharacterSize(DEFAULT_TEXT_CHAR_SIZE);
	text->setString(RESTART_TEXT);

	return text;
}