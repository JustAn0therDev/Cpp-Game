#pragma once
#include "Ui.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include <thread>
#include "Constants.hpp"
#include <memory>
#include <iostream>

void Ui::FadeOut(sf::Text& text) {
	if (!g_is_running_fade_animation) {
		g_is_running_fade_animation = true;

		sf::Color color = sf::Color::White;

		while (color.a > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			color.a -= 1;
			text.setFillColor(color);
		}

		g_is_running_fade_animation = false;
	}
}