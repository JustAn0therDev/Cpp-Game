#include "SnakePart.hpp"
#include <iostream>

SnakePart::SnakePart(sf::RectangleShape& rect) {
	m_rect = rect;
	m_lastPosition = rect.getPosition();
}