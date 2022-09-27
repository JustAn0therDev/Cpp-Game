#pragma once
#include "Ui.hpp"
#include <SFML/Graphics.hpp>
#include <thread>
#include "Constants.hpp"
#include <memory>
#include <iostream>

bool Ui::m_is_running_fade_animation;

Ui::Ui() : m_font(sf::Font()) {
	if (!m_font.loadFromFile(FONT_PATH)) {
		std::cout << "Could not open font file.\n";
		exit(1);
	}
}

void Ui::FadeOut(sf::Text* text) {
	if (!m_is_running_fade_animation) {
		m_is_running_fade_animation = true;

		sf::Color color = sf::Color::White;

		while (color.a > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			color.a -= 1;
			text->setFillColor(color);
		}

		m_is_running_fade_animation = false;
	}
}

sf::Text* Ui::MakeText(const sf::Color& text_color, unsigned int char_size, const std::string& string) {
	sf::Text* text = new sf::Text;
	text->setFont(m_font);
	text->setFillColor(text_color);
	text->setCharacterSize(char_size);
	text->setString(string);

	return text;
}