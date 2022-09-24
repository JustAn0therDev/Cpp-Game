#include <iostream>
#include <SFML/Graphics.hpp>
#include "Orientation.hpp"
#include "SnakePart.hpp"
#include "Snake.hpp"
#include <chrono>
#include <thread>
#include <random>
#include <vector>

static const float MOVE_BY = 10.0f;
static const int SLEEP_MILLISECONDS = 50;
static const int SLEEP_MOVE_MILISECONDS = 20;

void MoveSnakeByOrientation(Snake& snake, const Orientation& orientation) {
	snake.m_Parts[0].m_LastPosition = snake.m_Parts[0].m_Rect.getPosition();

	switch (orientation) {
	case Orientation::UP:
		snake.m_Parts[0].m_Rect.move(0, -MOVE_BY);
		break;
	case Orientation::DOWN:
		snake.m_Parts[0].m_Rect.move(0, MOVE_BY);
		break;
	case Orientation::LEFT:
		snake.m_Parts[0].m_Rect.move(-MOVE_BY, 0);
		break;
	case Orientation::RIGHT:
		snake.m_Parts[0].m_Rect.move(MOVE_BY, 0);
		break;
	}

	for (int i = 1; i < snake.m_Parts.size(); i++) {
		snake.m_Parts[i].m_Rect.move(snake.m_Parts[i - 1].m_LastPosition);
	}
}

void ChangeOrientation(Orientation& orientation, const sf::Event& event) {
	switch (event.key.code)
	{
	case sf::Keyboard::Up:
		orientation = Orientation::UP;
		break;
	case sf::Keyboard::Down:
		orientation = Orientation::DOWN;
		break;
	case sf::Keyboard::Left:
		orientation = Orientation::LEFT;
		break;
	case sf::Keyboard::Right:
		orientation = Orientation::RIGHT;
		break;
	}
}

// TODO: make this better by getting the offset from the rectangle size, so that the player gets the apple
// by touching it (basically a bit faster version of this "collision detection"
bool Collided(const sf::RectangleShape& objA, const sf::CircleShape& objB) {
	return objA.getPosition() == objB.getPosition();
}

void MoveApple(sf::CircleShape& apple) {
	//std::random_device dev;
	//std::mt19937 rng(dev());
	//std::uniform_int_distribution<std::mt19937::result_type> distWidth(10, 1270);

	//float x = distWidth(rng);

	//std::mt19937 rng2(dev());
	//std::uniform_int_distribution<std::mt19937::result_type> distHeight(10, 700);

	//float y = distHeight(rng2);

	float x = apple.getPosition().x + 10;
	float y = apple.getPosition().y + 10;

	apple.move(x, y);
}

void AddPartToSnake(std::vector<SnakePart>& parts, const Orientation& orientation) {
	sf::RectangleShape new_snake_part(sf::Vector2f(25.0f, 25.0f));

	new_snake_part.setFillColor(sf::Color::Green);

	const sf::RectangleShape& last_part = parts[parts.size() - 1].m_Rect;

	const sf::Vector2f pos = last_part.getPosition();

	const sf::Vector2f size = last_part.getSize();

	switch (orientation) {
	case Orientation::UP:
		new_snake_part.setPosition(pos.x, pos.y - size.x);
		break;
	case Orientation::DOWN:
		new_snake_part.setPosition(pos.x, pos.y + size.x);
		break;
	case Orientation::LEFT:
		new_snake_part.setPosition(pos.x - size.x, pos.y);
		break;
	case Orientation::RIGHT:
		new_snake_part.setPosition(pos.x + size.x, pos.y);
		break;
	}

	parts.push_back(SnakePart(new_snake_part));
}

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Snek Gaem!!1");
	sf::RectangleShape first_part(sf::Vector2f(25.0f, 25.0f));

	first_part.setFillColor(sf::Color::Green);

	Snake snake;

	Orientation orientation = Orientation::DOWN;

	snake.m_Parts.push_back(SnakePart(first_part));

	sf::CircleShape apple(15.0f);
	apple.setFillColor(sf::Color::Red);
	apple.move(20.0f, 20.0f);

	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2f offset(0.0f, 0.0f);

		while (window.pollEvent(event))
		{
			ChangeOrientation(orientation, event);

			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		MoveSnakeByOrientation(snake, orientation);

		/* TODO: debug later
		std::cout << "Snake's head position: " << snake.m_Parts[0].m_Rect.getPosition().x << " " << snake.m_Parts[0].m_Rect.getPosition().y << std::endl;
		std::cout << "Apple's position: " << apple.getPosition().x << " " << apple.getPosition().y << std::endl;
		*/

		if (Collided(snake.m_Parts[0].m_Rect, apple)) {
			std::cout << "Collision detected!" << std::endl;
			MoveApple(apple);
			AddPartToSnake(snake.m_Parts, orientation);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLISECONDS));

		window.clear();

		for (const auto& snake_part : snake.m_Parts) {
			window.draw(snake_part.m_Rect);
		}

		window.draw(apple);
		window.display();
	}

	return EXIT_SUCCESS;
}