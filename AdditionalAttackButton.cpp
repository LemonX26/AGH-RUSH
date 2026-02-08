#include "AdditionalAttackButton.h"
#include <iostream>

AdditionalAttackButton::AdditionalAttackButton(float x, float y, float width, float height, sf::Color color): Button(x - 17, y - 55, 80, 80, nullptr, "", color, sf::Color(200, 200, 200, 100),
sf::Color(200, 50, 180, 180))
{
	//Button(x - 25, y - 25, 50, 50, nullptr, "", sf::Color::Transparent, sf::Color(200, 200, 200, 100),
	//	sf::Color(200, 10, 200, 200));
	this->sprite = new sf::Sprite();
	this->texture = new sf::Texture();

	this->sprite->setTextureRect(sf::IntRect(0, 0, 100, 100));
	if(color==sf::Color::Red)
		this->texture->loadFromFile("characters_images/fire_attack.png");
	else if (color == sf::Color::Blue)
		this->texture->loadFromFile("characters_images/slowAttack.png");

	this->sprite->setTexture(*this->texture);
	this->sprite->setPosition(x-10, y-50);
}

AdditionalAttackButton::~AdditionalAttackButton()
{
}

void AdditionalAttackButton::render(sf::RenderTarget* target)
{
	Button::render(target);
	target->draw(*this->sprite);
}

/*
void AdditionalAttackButton::update(const sf::Vector2f mousePos, const float& dt)
{
	Button::update(mousePos);
	for (auto& a : this->buttons)
	{
		a->update(mousePos);
		if (a->isPressed())
		{
			std::cout << "chujjjjjjjjjjjj" << std::endl;
		}
	}
}
*/

void AdditionalAttackButton::update(const sf::Vector2f mousePos)//, const float& dt
{
	Button::update(mousePos);
	
	for (auto& e : this->buttons)
	{
		e->update(mousePos);
		if (e->isPressed())
		{
			std::cout << "chuj" << "\n";
		}

	}
	
}

void AdditionalAttackButton::onClick()
{
}

void AdditionalAttackButton::setEnabled(bool isEnabled)
{
	if (!isEnabled)
	{
		this->sprite->setColor(sf::Color(255, 255, 255, 100));
	}
	else
		this->sprite->setColor(sf::Color(255, 255, 255, 255));

	this->idleColor = sf::Color(255, 255, 255, 0);
	if (this->shape.getFillColor() == this->idleColor)
		this->shape.setFillColor(this->idleColor); 
	
}

/*
const bool AdditionalAttackButton::isPressed() const
{
	if(button)
	return false;
}
*/
