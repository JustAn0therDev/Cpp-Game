#pragma once
#include "SFML/Graphics.hpp"
#include "SnakePart.hpp"
#include <vector>

class Snake {
public:
	std::vector<SnakePart> m_parts;

	Snake() : m_parts(std::vector<SnakePart>()) {

	}
};
