#pragma once
#include "SFML/Graphics.hpp"
#include "SnakePart.hpp"
#include <vector>

class Snake {
public:
	std::vector<SnakePart> m_Parts;
	sf::Vector2f m_HeadsLastPositionBeforeChangingOrientation;

	Snake() : m_Parts(std::vector<SnakePart>()), m_HeadsLastPositionBeforeChangingOrientation(sf::Vector2f()) {

	}
};
