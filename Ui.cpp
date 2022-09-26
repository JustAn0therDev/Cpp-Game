#pragma once
#include "Ui.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include <thread>
#include "Constants.hpp"

void Ui::FadeOut(sf::Text& text) {
	if (!g_is_running_fade_animation) {
		g_is_running_fade_animation = true;

		sf::Color color = sf::Color::White;

		while (color.a > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
			color.a -= 1;
			text.setFillColor(color);
		}

		g_is_running_fade_animation = false;
	}
}

void Ui::InitializeRestartingText(sf::Text& text, const sf::Font& font) {
	text.setFont(font);

	text.setFillColor(DEFAULT_TRANSPARENT_WHITE_COLOR);

	text.setCharacterSize(DEFAULT_TEXT_CHAR_SIZE);

	text.setString(RESTART_TEXT);

	const float restart_text_x_pos = (static_cast<float>(DEFAULT_WIDTH) - text.getGlobalBounds().width) / 2;

	const float restart_text_y_pos = (static_cast<float>(DEFAULT_HEIGHT) - text.getGlobalBounds().height) / 2;

	text.setPosition(restart_text_x_pos, restart_text_y_pos);
}