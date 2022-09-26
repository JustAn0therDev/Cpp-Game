#include <iostream>
#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "SnakePart.hpp"
#include "Snake.hpp"
#include <chrono>
#include <thread>
#include <random>
#include <vector>

static const float SPEED = 10.0f;
static const int SLEEP_MILLISECONDS = 50;
static const int SLEEP_MOVE_MILISECONDS = 20;
static const int DEFAULT_WIDTH = 600;
static const int DEFAULT_HEIGHT = 400;
static const sf::Color DEFAULT_TRANSPARENT_WHITE_COLOR = sf::Color(255, 255, 255, 0);
static const sf::Vector2f DEFAULT_APPLE_SPAWN_POSITION = sf::Vector2f(30.0f, 30.0f);
static const float APPLE_RADIUS = 15.0f;
static const int APPLE_DIAMETER = static_cast<int>(APPLE_RADIUS * 1.5f);

static bool g_is_running_fade_animation = false;

void MoveSnakeByDirection(Snake& snake, const Direction& direction) {
	snake.m_parts[0].m_lastPosition = snake.m_parts[0].m_rect.getPosition();

	switch (direction) {
	case Direction::Up:
		snake.m_parts[0].m_rect.move(0, -SPEED);
		break;
	case Direction::Down:
		snake.m_parts[0].m_rect.move(0, SPEED);
		break;
	case Direction::Left:
		snake.m_parts[0].m_rect.move(-SPEED, 0);
		break;
	case Direction::Right:
		snake.m_parts[0].m_rect.move(SPEED, 0);
		break;
	}

	for (int i = 1; i < snake.m_parts.size(); i++) {
		snake.m_parts[i].m_lastPosition = snake.m_parts[i].m_rect.getPosition();
		snake.m_parts[i].m_rect.setPosition(snake.m_parts[i - 1].m_lastPosition);
	}
}

void ChangeDirection(Direction& direction, const sf::Event& event) {
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		if (direction != Direction::Down) {
			direction = Direction::Up;
		}
		break;
	case sf::Keyboard::Down:
		if (direction != Direction::Up) {
			direction = Direction::Down;
		}
		break;
	case sf::Keyboard::Left:
		if (direction != Direction::Right) {
			direction = Direction::Left;
		}
		break;
	case sf::Keyboard::Right:
		if (direction != Direction::Left) {
			direction = Direction::Right;
		}
		break;
	}
}

bool Collided(const sf::Shape& objA, const sf::Shape& objB) {
	return objA.getGlobalBounds().intersects(objB.getGlobalBounds());
}

bool SnakeCollidedWithItself(const Snake& snake) {
	for (int i = 1; i < snake.m_parts.size(); i++) {
		if (snake.m_parts[i].m_rect.getPosition() == snake.m_parts[0].m_rect.getPosition()) {
			return true;
		}
	}

	return false;
}

bool SnakeIsOutOfBounds(const SnakePart& snake_head) {
	sf::Vector2f snake_head_pos = snake_head.m_rect.getPosition();

	return snake_head_pos.x < 0 ||
		   snake_head_pos.y < 0 ||
		   snake_head_pos.x >= DEFAULT_WIDTH ||
		   snake_head_pos.y >= DEFAULT_HEIGHT;
}

void MoveApple(sf::CircleShape& apple) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distWidth(APPLE_DIAMETER, DEFAULT_WIDTH - APPLE_DIAMETER);

	float x = static_cast<float>(ceil(distWidth(rng) / 10) * 10);

	std::mt19937 rng2(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distHeight(APPLE_DIAMETER, DEFAULT_HEIGHT - APPLE_DIAMETER);

	float y = static_cast<float>(ceil(distHeight(rng2) / 10) * 10);

	apple.setPosition(x, y);
}

void AddPartToSnake(std::vector<SnakePart>& parts, const Direction& direction) {
	sf::RectangleShape new_snake_part(sf::Vector2f(25.0f, 25.0f));

	new_snake_part.setFillColor(sf::Color::Green);

	const SnakePart& last_part = parts[parts.size() - 1];

	new_snake_part.setPosition(last_part.m_lastPosition);

	parts.push_back(SnakePart(new_snake_part));
}

void FadeOut(sf::Text& text) {
	if (!g_is_running_fade_animation) {
		g_is_running_fade_animation = true;

		sf::Color color = sf::Color::White;
		while (color.a > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
			color.a -= 1;
			text.setFillColor(color);
		}

		g_is_running_fade_animation = false;
	}
}

void InitializeSnake(Snake& snake) {
	sf::RectangleShape first_part(sf::Vector2f(25.0f, 25.0f));

	first_part.setFillColor(sf::Color::Green);

	snake.m_parts.push_back(SnakePart(first_part));
}

void RestartGame(Snake& snake, sf::Shape& apple, Direction& direction) {
	snake.~Snake();
	
	snake = Snake();

	InitializeSnake(snake);

	apple.setPosition(DEFAULT_APPLE_SPAWN_POSITION);
	
	direction = Direction::Down;
}

int main() {
	sf::RenderWindow window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Snek Gaem!!1");
	Snake snake;

	InitializeSnake(snake);

	Direction direction = Direction::Down;

	sf::CircleShape apple(APPLE_RADIUS);
	apple.setFillColor(sf::Color::Red);
	apple.setPosition(DEFAULT_APPLE_SPAWN_POSITION);

	sf::Font font;

	if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
		std::cout << "Could not open font file.\n";
		return EXIT_FAILURE;
	}

	sf::Text text;

	text.setFont(font);

	text.setFillColor(DEFAULT_TRANSPARENT_WHITE_COLOR);

	text.setCharacterSize(24);

	text.setString("restarting");

	const float restart_text_x_pos = (static_cast<float>(DEFAULT_WIDTH) - text.getGlobalBounds().width) / 2;

	const float restart_text_y_pos = (static_cast<float>(DEFAULT_HEIGHT) - text.getGlobalBounds().height) / 2;

	text.setPosition(restart_text_x_pos, restart_text_y_pos);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			ChangeDirection(direction, event);

			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Key::Escape) {
				window.close();
			}
		}

		MoveSnakeByDirection(snake, direction);

		if (Collided(snake.m_parts[0].m_rect, apple)) {
			MoveApple(apple);
			AddPartToSnake(snake.m_parts, direction);
		}
		else if (SnakeCollidedWithItself(snake) || SnakeIsOutOfBounds(snake.m_parts[0])) {
			std::thread thread(FadeOut, std::ref(text));
			thread.detach();
			RestartGame(snake, apple, direction);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLISECONDS));

		window.clear();

		for (const auto& snake_part : snake.m_parts) {
			window.draw(snake_part.m_rect);
		}

		window.draw(apple);
		
		if (text.getFillColor().a > 0) {
			window.draw(text);
		}
		
		window.display();
	}

	while (window.waitEvent(event)) {
		if (event.key.code == sf::Keyboard::Enter || event.type == sf::Event::Closed) {
			break;
		}
	}

	return EXIT_SUCCESS;
}