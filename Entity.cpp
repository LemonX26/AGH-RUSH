#include "Entity.h"

#include <iostream>

Entity::Entity()
{
	this->texture = new sf::Texture;
	this->texture->loadFromFile("Resources/default.png");
	this->model = new sf::Sprite(*this->texture);
}

Entity::~Entity()
{
}
/*
sf::Vector2i Entity::getPosition()
{
	return sf::Vector2i(this->model->getPosition().x, this->model->getPosition().y);
	//return sf::Vector2i(this->shape.getGlobalBounds().getPosition().x, this->shape.getGlobalBounds().getPosition().y);
}
*/
const sf::Sprite Entity::getShape() const
{
	return *this->model;
}



