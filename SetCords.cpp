#include "SetCords.h"

using namespace std;

sf::Vector2f SetCords::get_Random_Cord()
{
	//
	//srand(time(NULL));
	int random = generate_wariation_path();
	random_position_x = (float)(rand() % (start_position[random][1] - start_position[random][0]) + start_position[random][0]);
	random_position_y = (float)(rand() % (start_position[random][3] - start_position[random][2]) + start_position[random][2]);
	return sf::Vector2f(this->random_position_x, this->random_position_y);
}

int SetCords::generate_wariation_path()
{
	
	random_position = rand() % 2;
	return random_position;
}

