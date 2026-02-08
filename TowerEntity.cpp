#include "TowerEntity.h"

#include <iostream>

void TowerEntity::update(const float& dt)
{
	this->updateRotation(this->targetPosition);
	
}

void TowerEntity::setPosition(float x, float y)
{
	this->position.x = x;
	this->position.y = y;
	this->model->setPosition(x, y);
}

void TowerEntity::setAimPoint(float angle)
{
	//gets the coordinates from angle and radius
	float x = this->model->getPosition().x - cos(angle * 3.14159265 / 180) * this->towerRadius;
	float y = this->model->getPosition().y - sin(angle * 3.14159265 / 180) * this->towerRadius;
	this->aimPoint.x = x;
	this->aimPoint.y = y;
	std::cout << "AIM POINT x: "<<x <<" y: "<<y<<std::endl;
}

void TowerEntity::updateRotation(sf::Vector2i targetPosition)
{
	sf::Vector2f direction;
	direction.x = targetPosition.x - this->position.x;
	direction.y = targetPosition.y - this->position.y;
	float angle = atan2(direction.y, direction.x) * 180 / 3.14159265;
	this->aimHighlighter->setRotation(angle);
}

void TowerEntity::initRadiusHighlighter()
{
	this->radiusHighlighter = new sf::CircleShape(this->towerRadius);
	this->radiusHighlighter->setFillColor(sf::Color::Transparent);
	this->radiusHighlighter->setOutlineColor(sf::Color::Red);
	this->radiusHighlighter->setOutlineThickness(1.f);
	this->radiusHighlighter->setPosition(this->position.x- this->towerRadius, this->position.y- this->towerRadius);
}

void TowerEntity::initAimPointHighlighter()
{
	this->aimPointHighlighter = new sf::CircleShape(5.f);
	this->aimPointHighlighter->setFillColor(sf::Color::Cyan);
	this->aimPointHighlighter->setPosition(this->aimPoint.x, this->aimPoint.y);
}

void TowerEntity::initAimHighlighter()
{
	this->aimHighlighter = new sf::RectangleShape(sf::Vector2f(50.f, 5.f));
	this->aimHighlighter->setFillColor(sf::Color::Red);
	this->aimHighlighter->setPosition(this->position.x, this->position.y);
}

TowerEntity::TowerEntity(sf::Vector2f position, TowerType type)
{
	this->type = type;
	this->textureShoot = new sf::Texture();
	switch (type)
	{
	case TowerType::Ranger:
		this->texture->loadFromFile("characters_images/ranger.png");
		this->textureShoot->loadFromFile("characters_images/ranger_shoot.png");
		this->model->setTexture(*this->texture);
		break;
	case TowerType::Artillery:
		this->textureShoot->loadFromFile("characters_images/artillery_shoot.png");
		this->texture->loadFromFile("characters_images/artillery.png");
		this->model->setTexture(*this->texture);
		break;
	}

	this->model->setTextureRect(sf::IntRect(0, 0, 100, 100));
	this->setPosition(position.x-40, position.y-60);
	this->setAimPoint(-60 / 3.14159265);

	initAimHighlighter();
	initRadiusHighlighter();
	initAimPointHighlighter();
}

TowerEntity::~TowerEntity()
{
	delete this->model;
}


void TowerEntity::render(sf::RenderTarget* target)
{
	target->draw(*this->radiusHighlighter);
	target->draw(*this->aimPointHighlighter);
	target->draw(*this->model);
	target->draw(*this->aimHighlighter);
}


void TowerEntity::move(const float& dt, float x, float y)
{
}

void TowerEntity::setShoot(bool isShooting)
{
	if (isShooting)
	{
		model->setTexture(*textureShoot);
	}
	else
	{
		model->setTexture(*texture);
	}
}
