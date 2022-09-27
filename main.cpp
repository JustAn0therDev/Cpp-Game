#include <iostream>
#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include "SnakePart.hpp"
#include <thread>
#include "Constants.hpp"
#include "Ui.hpp"



int main() {
	sf::RenderWindow window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Snek Gaem!!1");
	window.setFramerateLimit(60);

	Game game;
	sf::Event event;
	
	Ui ui;

	sf::Text* text = ui.MakeText(DEFAULT_TRANSPARENT_WHITE_COLOR, DEFAULT_TEXT_CHAR_SIZE, RESTART_TEXT);

	const float restart_text_x_pos = (static_cast<float>(DEFAULT_WIDTH) - text->getGlobalBounds().width) / 2;

	const float restart_text_y_pos = (static_cast<float>(DEFAULT_HEIGHT) - text->getGlobalBounds().height) / 2;

	text->setPosition(restart_text_x_pos, restart_text_y_pos);

	sf::Text* apples_eaten_text = ui.MakeText(sf::Color::White, DEFAULT_TEXT_CHAR_SIZE, std::to_string(game.m_apples_eaten));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			game.m_snake.ChangeDirection(event);

			if (event.type == sf::Event::Closed || event.key.code == sf::Keyboard::Key::Escape) {
				window.close();
			}
		}

		game.m_snake.MoveSnakeByDirection();

		if (Game::Collided(game.m_snake.m_parts[0].m_rect, game.m_apple)) {
			game.MoveApple();
			game.m_snake.AddPart();
			game.m_apples_eaten++;
		}
		else if (game.SnakeCollidedWithItself() || game.SnakeIsOutOfBounds()) {
			ui.FadeOut(text);
			game = Game();
		}

		window.clear();

		for (const auto& snake_part : game.m_snake.m_parts) {
			window.draw(snake_part.m_rect);
		}

		window.draw(game.m_apple);

		if (text->getFillColor().a > 0) {
			window.draw(*text);
		}

		apples_eaten_text->setString(std::to_string(game.m_apples_eaten));
		window.draw(*apples_eaten_text);

		window.display();
	}

	delete text;
	delete apples_eaten_text;

	return EXIT_SUCCESS;
}