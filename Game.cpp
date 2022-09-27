#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "Constants.hpp"
#include <chrono>
#include <random>

Game::Game() : m_snake(Snake()), m_apple(sf::CircleShape(APPLE_RADIUS)), m_apples_eaten(0) {
	m_apple.setFillColor(sf::Color::Red);
	m_apple.setPosition(DEFAULT_APPLE_SPAWN_POSITION);
}

void Game::MoveApple() {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distWidth(APPLE_DIAMETER, DEFAULT_WIDTH - APPLE_DIAMETER);

	float x = static_cast<float>(ceil(distWidth(rng) / 10) * 10);

	std::mt19937 rng2(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distHeight(APPLE_DIAMETER, DEFAULT_HEIGHT - APPLE_DIAMETER);

	float y = static_cast<float>(ceil(distHeight(rng2) / 10) * 10);

	m_apple.setPosition(x, y);
}

bool Game::Collided(const sf::Shape& objA, const sf::Shape& objB) {
	return objA.getGlobalBounds().intersects(objB.getGlobalBounds());
}

bool Game::SnakeCollidedWithItself() {
	for (int i = 1; i < m_snake.m_parts.size(); i++) {
		if (m_snake.m_parts[i].m_rect.getPosition() == m_snake.m_parts[0].m_rect.getPosition()) {
			return true;
		}
	}

	return false;
}

bool Game::SnakeIsOutOfBounds() {
	sf::Vector2f snake_head_pos = m_snake.m_parts[0].m_rect.getPosition();

	return snake_head_pos.x < 0 ||
		snake_head_pos.y < 0 ||
		snake_head_pos.x >= DEFAULT_WIDTH ||
		snake_head_pos.y >= DEFAULT_HEIGHT;
}