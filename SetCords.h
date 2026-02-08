#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;
class SetCords
{
public:

	//path cords

	int NUMBER_OF_ENEMIES = 17;
	
	int random_position; //generate first possibly path
	
	float random_position_x; //generate possibly path_x
	
	float random_position_y; //generate possibly path_y
	
	int start_position[2][4] = //array of paths
	{  // x1   x2	 y1	  y2
		{ 970,	910, -200,  0 },
		{ 1680, 1580, 870,1020 },
	};
	//generating random cords
	sf::Vector2f get_Random_Cord();
	int generate_wariation_path();
	
	
};

