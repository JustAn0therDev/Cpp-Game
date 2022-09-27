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

	Game game;
	sf::Event event;
	
	sf::Text apples_eaten_text;

	Ui ui;

	sf::Text* text = ui.CreateText();

	apples_eaten_text.setFont(ui.m_font);
	apples_eaten_text.setFillColor(sf::Color::White);
	apples_eaten_text.setCharacterSize(DEFAULT_TEXT_CHAR_SIZE);
	apples_eaten_text.setString(std::to_string(game.m_apples_eaten));

	const float restart_text_x_pos = (static_cast<float>(DEFAULT_WIDTH) - text->getGlobalBounds().width) / 2;

	const float restart_text_y_pos = (static_cast<float>(DEFAULT_HEIGHT) - text->getGlobalBounds().height) / 2;

	text->setPosition(restart_text_x_pos, restart_text_y_pos);

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
			std::thread thread(ui.FadeOut, text);
			thread.detach();
			game = Game();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLISECONDS));

		window.clear();

		for (const auto& snake_part : game.m_snake.m_parts) {
			window.draw(snake_part.m_rect);
		}

		window.draw(game.m_apple);

		if (text->getFillColor().a > 0) {
			window.draw(*text);
		}

		apples_eaten_text.setString(std::to_string(game.m_apples_eaten));
		window.draw(apples_eaten_text);

		window.display();
	}

	return EXIT_SUCCESS;
}