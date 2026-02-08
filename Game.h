
#ifndef GAME_H
#define GAME_H

#include "GameState.h"
#include "MainMenuState.h"


class Game
{
private:
	
	//Variables
	sf::RenderWindow window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	float dt;

	std::map<std::string,int> supportedKeys;

	std::stack<State*> states;

	//Init
	void initStates();
	void initWindow();
	void initKeys();
public:
	//Constructors/Destructors

	Game();
	virtual ~Game();

	//Functions
	//Regular
	void endApplication();
	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();
	
	//Render
	void render();

	//Core
	void run();
};
#endif

