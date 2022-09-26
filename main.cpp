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

	sf::Font font;
	sf::Text text;
	sf::Event event;

	if (!font.loadFromFile("PressStart2P-Regular.ttf")) {
		std::cout << "Could not open font file.\n";
		return EXIT_FAILURE;
	}

	Ui::InitializeRestartingText(text, font);

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
		}
		else if (game.SnakeCollidedWithItself() || game.SnakeIsOutOfBounds()) {
			std::thread thread(Ui::FadeOut, std::ref(text));
			thread.detach();
			game = Game();
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_MILLISECONDS));

		window.clear();

		for (const auto& snake_part : game.m_snake.m_parts) {
			window.draw(snake_part.m_rect);
		}

		window.draw(game.m_apple);

		if (text.getFillColor().a > 0) {
			window.draw(text);
		}

		window.display();
	}

	return EXIT_SUCCESS;
}