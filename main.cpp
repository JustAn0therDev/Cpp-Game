#include <iostream>
#include <SFML/Graphics.hpp>
#include "Direction.hpp"
#include "Game.hpp"
#include "Snake.hpp"
#include "SnakePart.hpp"
#include <thread>
#include "Constants.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(DEFAULT_WIDTH, DEFAULT_HEIGHT), "Snek Gaem!!1");
	window.setFramerateLimit(60);

	Game game;
	sf::Event event;
	sf::Font font;
	sf::Text restart_text;
	sf::Text apples_eaten_text;

	if (!font.loadFromFile(FONT_PATH)) {
		std::cout << "Could not open font file.\n";
		exit(1);
	}
	
	restart_text.setFont(font);
	restart_text.setFillColor(DEFAULT_TRANSPARENT_WHITE_COLOR);
	restart_text.setCharacterSize(DEFAULT_TEXT_CHAR_SIZE);
	restart_text.setString(RESTART_TEXT);

	const float restart_text_x_pos = (static_cast<float>(DEFAULT_WIDTH) - restart_text.getGlobalBounds().width) / 2;

	const float restart_text_y_pos = (static_cast<float>(DEFAULT_HEIGHT) - restart_text.getGlobalBounds().height) / 2;

	restart_text.setPosition(restart_text_x_pos, restart_text_y_pos);

	sf::Color restart_text_color = sf::Color::White;

	apples_eaten_text.setFont(font);
	apples_eaten_text.setFillColor(sf::Color::White);
	apples_eaten_text.setCharacterSize(DEFAULT_TEXT_CHAR_SIZE);
	apples_eaten_text.setString(std::to_string(game.m_apples_eaten));

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
			restart_text_color.a = 255;
			game = Game();
		}

		window.clear();

		for (const auto& snake_part : game.m_snake.m_parts) {
			window.draw(snake_part.m_rect);
		}

		window.draw(game.m_apple);

		if (restart_text_color.a > 0) {
			restart_text_color.a -= 5;
			restart_text.setFillColor(restart_text_color);
		}

		window.draw(restart_text);
		
		apples_eaten_text.setString(std::to_string(game.m_apples_eaten));
		window.draw(apples_eaten_text);

		window.display();
	}

	return EXIT_SUCCESS;
}