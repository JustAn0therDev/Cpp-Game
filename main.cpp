#include <iostream>
#include <SFML/Graphics.hpp>

const float MOVE_BY = 20.0f;

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::CircleShape shape(50.f);
    shape.setFillColor(sf::Color::Magenta);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Vector2f offset(0.0f, 0.0f);

        while (window.pollEvent(event))
        {
            switch (event.key.code)
            {
                case sf::Keyboard::Up:
                    shape.move(0, -MOVE_BY);
                    break;
                case sf::Keyboard::Down:
                    shape.move(0, MOVE_BY);
                    break;
                case sf::Keyboard::Left:
                    shape.move(-MOVE_BY, 0);
                    break;
                case sf::Keyboard::Right:
                    shape.move(MOVE_BY, 0);
                    break;
                default:
                    break;
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}