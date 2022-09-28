#include "Snake.hpp"
#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Constants.hpp"

Snake::Snake() : m_parts(std::vector<SnakePart>()), m_direction(Direction::Down) {
	m_parts.reserve(150);

	sf::RectangleShape first_part(sf::Vector2f(SNAKE_DIAMETER, SNAKE_DIAMETER));

	first_part.setFillColor(sf::Color::Green);

	m_parts.emplace_back(first_part);
}

void Snake::MoveSnakeByDirection() {
	m_parts[0].m_lastPosition = m_parts[0].m_rect.getPosition();

	switch (m_direction) {
	case Direction::Up:
		m_parts[0].m_rect.move(0, -SPEED);
		break;
	case Direction::Down:
		m_parts[0].m_rect.move(0, SPEED);
		break;
	case Direction::Left:
		m_parts[0].m_rect.move(-SPEED, 0);
		break;
	case Direction::Right:
		m_parts[0].m_rect.move(SPEED, 0);
		break;
	}

	for (int i = 1; i < m_parts.size(); i++) {
		m_parts[i].m_lastPosition = m_parts[i].m_rect.getPosition();
		m_parts[i].m_rect.setPosition(m_parts[i - 1].m_lastPosition);
	}
}

void Snake::ChangeDirection(const sf::Event& event) {
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		if (m_direction != Direction::Down) {
			m_direction = Direction::Up;
		}
		break;
	case sf::Keyboard::Down:
		if (m_direction != Direction::Up) {
			m_direction = Direction::Down;
		}
		break;
	case sf::Keyboard::Left:
		if (m_direction != Direction::Right) {
			m_direction = Direction::Left;
		}
		break;
	case sf::Keyboard::Right:
		if (m_direction != Direction::Left) {
			m_direction = Direction::Right;
		}
		break;
	}
}

void Snake::AddPart() {
	sf::RectangleShape new_snake_part(sf::Vector2f(SNAKE_DIAMETER, SNAKE_DIAMETER));

	new_snake_part.setFillColor(sf::Color::Green);

	const SnakePart& last_part = m_parts[m_parts.size() - 1];

	new_snake_part.setPosition(last_part.m_lastPosition);

	m_parts.emplace_back(new_snake_part);
}