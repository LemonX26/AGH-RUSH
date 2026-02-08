#pragma once


#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <fstream>
#include <sstream>

#include <stack>
#include <map>
#include <vector>

enum button_states { BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE };
class Button
{

	private:
	short unsigned buttonState;


	
	sf::Font* font;
	sf::Text text;

	sf::Color hoverColor;
	sf::Color activeColor;

	protected:
		sf::RectangleShape shape;
		sf::Color idleColor;
public:
	Button(float x,float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
	~Button();

	//Functions
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f mousePos);

	//Accessors
	const bool isPressed() const;

};

