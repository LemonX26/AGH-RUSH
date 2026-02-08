#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
sf::Vector2f alignToCurrentPosition(sf::RenderWindow* window, sf::Vector2f rawPosotion);
double getDistance(sf::Vector2i a, sf::Vector2i b);
