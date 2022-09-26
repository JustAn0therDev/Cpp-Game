#pragma once
#include <SFML/Graphics.hpp>

const float SPEED = 10.0f;
const int SLEEP_MILLISECONDS = 50;
const int SLEEP_MOVE_MILISECONDS = 20;
const int DEFAULT_WIDTH = 600;
const int DEFAULT_HEIGHT = 400;
const sf::Color DEFAULT_TRANSPARENT_WHITE_COLOR = sf::Color(255, 255, 255, 0);
const sf::Vector2f DEFAULT_APPLE_SPAWN_POSITION = sf::Vector2f(30.0f, 30.0f);
const float APPLE_RADIUS = 15.0f;
const int APPLE_DIAMETER = static_cast<int>(APPLE_RADIUS * 1.5f);
const char RESTART_TEXT[11] = "restarting";
const int DEFAULT_TEXT_CHAR_SIZE = 24;