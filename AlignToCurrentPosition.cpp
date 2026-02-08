
#include "AlignToCurrentPosition.h"

#include <iostream>

sf::Vector2f alignToCurrentPosition(sf::RenderWindow* window, sf::Vector2f rawPosotion)
{
	sf::Vector2f alignedPosition;
	alignedPosition.x = rawPosotion.x * window->getSize().x/1920.f;
	alignedPosition.y = rawPosotion.y * window->getSize().y/1080.f;
	//std::cout<< "x: " << alignedPosition.x << " y: " << alignedPosition.y << std::endl;
	return alignedPosition;
}

double getDistance(sf::Vector2i point1, sf::Vector2i point2)
{
	double distance = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
	return distance;
}
