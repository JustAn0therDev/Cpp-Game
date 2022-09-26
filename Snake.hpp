#pragma once
#include "SFML/Graphics.hpp"
#include "SnakePart.hpp"
#include <vector>
#include "Direction.hpp"

class Snake {
public:
	std::vector<SnakePart> m_parts;
	Direction m_direction;

	Snake();

	void ChangeDirection(const sf::Event& event);
	void MoveSnakeByDirection();
	void AddPart();
};
