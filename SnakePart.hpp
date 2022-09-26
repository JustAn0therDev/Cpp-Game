#pragma once
#include <SFML/Graphics.hpp>

class SnakePart {
public:
	sf::RectangleShape m_rect;
	sf::Vector2f m_lastPosition;

	SnakePart(sf::RectangleShape& rect) {
		m_rect = rect;
		m_lastPosition = rect.getPosition();
	}
};