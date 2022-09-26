#include <iostream>
#include <SFML/Graphics.hpp>
#include "Orientation.hpp"
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

void MoveSnakeByOrientation(Snake& snake, const Orientation& orientation) {
	snake.m_Parts[0].m_LastPosition = snake.m_Parts[0].m_Rect.getPosition();

	switch (orientation) {
	case Orientation::UP:
		snake.m_Parts[0].m_Rect.move(0, -SPEED);
		break;
	case Orientation::DOWN:
		snake.m_Parts[0].m_Rect.move(0, SPEED);
		break;
	case Orientation::LEFT:
		snake.m_Parts[0].m_Rect.move(-SPEED, 0);
		break;
	case Orientation::RIGHT:
		snake.m_Parts[0].m_Rect.move(SPEED, 0);
		break;
	}

	for (int i = 1; i < snake.m_Parts.size(); i++) {
		snake.m_Parts[i].m_LastPosition = snake.m_Parts[i].m_Rect.getPosition();
		snake.m_Parts[i].m_Rect.setPosition(snake.m_Parts[i - 1].m_LastPosition);
	}
}

void ChangeOrientation(Orientation& orientation, const sf::Event& event) {
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		if (orientation != Orientation::DOWN) {
			orientation = Orientation::UP;
		}
		break;
	case sf::Keyboard::Down:
		if (orientation != Orientation::UP) {
			orientation = Orientation::DOWN;
		}
		break;
	case sf::Keyboard::Left:
		if (orientation != Orientation::RIGHT) {
			orientation = Orientation::LEFT;
		}
		break;
	case sf::Keyboard::Right:
		if (orientation != Orientation::LEFT) {
			orientation = Orientation::RIGHT;
		}
		break;
	}
}

bool Collided(const sf::Shape& objA, const sf::Shape& objB) {
	return objA.getGlobalBounds().intersects(objB.getGlobalBounds());
}

bool SnakeCollidedWithItself(const Snake& snake) {
	for (int i = 1; i < snake.m_Parts.size(); i++) {
		if (snake.m_Parts[i].m_Rect.getPosition() == snake.m_Parts[0].m_Rect.getPosition()) {
			return true;
		}
	}

	return false;
}

bool SnakeIsOutOfBounds(const SnakePart& snake_head) {
	sf::Vector2f snake_head_pos = snake_head.m_Rect.getPosition();

	return snake_head_pos.x < 0 ||
		   snake_head_pos.y < 0 ||
		   snake_head_pos.x >= DEFAULT_WIDTH ||
		   snake_head_pos.y >= DEFAULT_HEIGHT;
}

void MoveApple(sf::CircleShape& apple) {
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distWidth(10, DEFAULT_WIDTH - 10);

	float x = static_cast<float>(ceil(distWidth(rng) / 10) * 10);

	std::mt19937 rng2(dev());
	std::uniform_int_distribution<std::mt19937::result_type> distHeight(10, DEFAULT_HEIGHT - 10);

	float y = static_cast<float>(ceil(distHeight(rng2) / 10) * 10);

	apple.setPosition(x, y);
}

void AddPartToSnake(std::vector<SnakePart>& parts, const Orientation& orientation) {
	sf::RectangleShape new_snake_part(sf::Vector2f(25.0f, 25.0f));

	new_snake_part.setFillColor(sf::Color::Green);

	const SnakePart& last_part = parts[parts.size() - 1];

	new_snake_part.setPosition(last_part.m_LastPosition);

	parts.push_back(SnakePart(new_snake_part));
}

int main() {
	sf::RenderWindow window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Snek Gaem!!1");
	sf::RectangleShape first_part(sf::Vector2f(25.0f, 25.0f));

	first_part.setFillColor(sf::Color::Green);

	Snake snake;

	Orientation orientation = Orientation::DOWN;

	snake.m_Parts.push_back(SnakePart(first_part));

	sf::CircleShape apple(15.0f);
	apple.setFillColor(sf::Color::Red);
	apple.move(20.0f, 20.0f);

	sf::Font font;

	if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
		std::cout << "Could not open font file." << std::endl;
		return EXIT_FAILURE;
	}

	sf::Text text;

	sf::Color restart_text_color = sf::Color::White;

	text.setFont(font);

	text.setFillColor(sf::Color::White);

	text.setCharacterSize(24);

	text.setString("restarting");

	const float restart_text_x_pos = (static_cast<float>(DEFAULT_WIDTH) - text.getGlobalBounds().width) / 2;

	const float restart_text_y_pos = (static_cast<float>(DEFAULT_HEIGHT) - text.getGlobalBounds().height) / 2;

	text.setPosition(restart_text_x_pos, restart_text_y_pos);

	sf::Event event;

	bool game_over = false, called_fade = false;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			ChangeOrientation(orientation, event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		if (!game_over) {
			MoveSnakeByOrientation(snake, orientation);

			if (Collided(snake.m_Parts[0].m_Rect, apple)) {
				MoveApple(apple);
				AddPartToSnake(snake.m_Parts, orientation);
			}
			else if (SnakeCollidedWithItself(snake) || SnakeIsOutOfBounds(snake.m_Parts[0])) {
				called_fade = true;
				game_over = true;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLISECONDS));

		window.clear();

		for (const auto& snake_part : snake.m_Parts) {
			window.draw(snake_part.m_Rect);
		}

		window.draw(apple);
	
		if (game_over) {
			if (restart_text_color.a > 0) {
				restart_text_color.a -= 5;
				text.setFillColor(restart_text_color);
			}

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