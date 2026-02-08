#include "TowerSelectorElement.h"


void TowerSelectorElement::render(sf::RenderTarget* target)
{
	Button::render(target);
	 target->draw(*this->sprite);
}

TowerSelectorElement::TowerSelectorElement(float x, float y, TowerType type, sf::Color color): Button(
	x - 25, y - 25, 50, 50, nullptr, "", color, sf::Color(200, 200, 200, 100),
	sf::Color(200, 10, 200, 200))
{
	this->texture = new sf::Texture();
	this->sprite = new sf::Sprite();
	if (type == TowerType::Artillery)
	{
		this->texture->loadFromFile("characters_images/artillery.png");
	}
	else
	{
		this->texture->loadFromFile("characters_images/ranger.png");
	}
	this->sprite->setTexture(*this->texture);
	this->sprite->setScale(0.5, 0.5);
	this->sprite->setPosition(x - 25, y - 25);


	this->type = type;
	//this->position = sf::Vector2f(x - 25, y - 25);
}
