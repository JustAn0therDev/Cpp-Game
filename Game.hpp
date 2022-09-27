#pragma once
#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include "Direction.hpp"

class Game {
public:
	Snake m_snake;
	sf::CircleShape m_apple;
	int m_apples_eaten;

	Game();

	void MoveApple();
	static bool Collided(const sf::Shape& objA, const sf::Shape& objB);
	bool SnakeCollidedWithItself();
	bool SnakeIsOutOfBounds();

};