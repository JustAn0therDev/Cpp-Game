#pragma once
#include <SFML/Graphics.hpp>
#include "Orientation.hpp"

class SnakePart {
public:
	sf::RectangleShape m_Rect;
	sf::Vector2f m_LastPosition;

	SnakePart(sf::RectangleShape& rect) {
		m_Rect = rect;
		m_LastPosition = rect.getPosition();
	}
};