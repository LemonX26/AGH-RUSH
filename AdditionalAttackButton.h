#pragma once
#include "Button.h"

class AdditionalAttackButton:public Button
{

private:
	sf::Vector2f position;
	std::vector<AdditionalAttackButton*> buttons;
	sf::Texture* texture;
	sf::Sprite* sprite;


public:
	AdditionalAttackButton(float x, float y, float width, float height, sf::Color color);//, float width, float height, 
	~AdditionalAttackButton();
	void render(sf::RenderTarget* target);
	void update(const sf::Vector2f mousePos);//,const float& 
	void onClick();
	void setEnabled(bool isEnabled);
	//void update(const sf::Vector2f mousePos, const float& dt);
	//const bool isPressed() const;
};

