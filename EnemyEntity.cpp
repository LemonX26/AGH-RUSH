#include "EnemyEntity.h"
#include <iostream>
#include <algorithm>

void EnemyEntity::initHpText()
{
	this->font = new sf::Font();
	this->font->loadFromFile("Fonts/Comfortaa-VariableFont_wght.ttf");
	this->hpText = new sf::Text();
	this->hpText->setString(std::to_string(static_cast<int>(this->hp)));
	this->hpText->setFillColor(sf::Color::Black);
	this->hpText->setCharacterSize(12);
	this->hpText->setOutlineColor(sf::Color::Cyan);
	this->hpText->setOutlineThickness(1.f);
	this->hpText->setFont(*this->font);
}

EnemyEntity::EnemyEntity()
{
	int random = rand() % 2;

	this->aliveTexture = new sf::Texture();
	this->deadTexture = new sf::Texture();
	if (random == 0)
	{
		this->deadTexture->loadFromFile("characters_images/dead_enemy1.png");
		this->aliveTexture->loadFromFile("characters_images/alive_enemy1.png");
	}
	else
	{
		this->deadTexture->loadFromFile("characters_images/dead_enemy2.png");
		this->aliveTexture->loadFromFile("characters_images/alive_enemy2.png");
	}
	this->model->setTextureRect(sf::IntRect(0, 0, 70, 120));
	this->model->setScale(0.4f, 0.4f);
	this->model->setTexture(*this->aliveTexture);

	initHpText();
}

EnemyEntity::~EnemyEntity()
{
}

void EnemyEntity::move(const float& dt, const float x, const float y)
{
	float multiplier = 1.f;
	if (this->isSlowed)
		multiplier = this->slowMultiplier;
	if (this->isAlive)
		this->model->move(x * this->movementSpeed * dt * multiplier, y * this->movementSpeed * dt * multiplier);
	

}

void EnemyEntity::updateSlowMultiplier(float multiplier)
{
	this->slowMultiplier = multiplier;
}

void EnemyEntity::setSlowed(bool slowed)
{
	this->isSlowed = slowed;
}


void EnemyEntity::getDamage(bool damage)
{
	if (this->isGiveDamage)
	{
		this->hp -= givenDamage;
		std::cout << "Damage given: " << givenDamage << "\n";
	}
	if (hp <= 0)
	{
		this->isAlive = false;
		this->hp = 0;
		this->model->setTexture(*this->deadTexture);
	}
	this->isGiveDamage = damage;
}



void EnemyEntity::updateGetDamage(float givendamage)
{
	this->isGiveDamage = givendamage;
}

bool EnemyEntity::checkIsEnemyAlive(bool isalive)
{
	if (isalive)
	{
		return true;
	}
	if (!isalive)
	{
		return false;
	}
}

void EnemyEntity::update(const float& dt)
{
	this->updateHpText();
}

void EnemyEntity::updateHpText()
{
	this->hpText->setPosition(this->model->getPosition().x, this->model->getPosition().y - 20);
	this->hpText->setString(std::to_string(static_cast<int>(this->hp)));
}


bool EnemyEntity::endOfWave() //Entity* target
{
	if (((model->getPosition().x < 0) || model->getPosition().y < 0) || !this->isAlive)
	{
		return true;
	}
	return false;
}

void EnemyEntity::takeDamage(float damage)
{
	this->hp -= damage;
	if (this->hp <= 0)
	{
		this->hp = 0;
		this->isAlive = false;
		this->model->setTexture(*this->deadTexture);
	}
}

sf::Vector2f EnemyEntity::mouse_position()
{
	return sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

void EnemyEntity::render(sf::RenderTarget* target)
{
	target->draw(*this->model);
	target->draw(*this->hpText);
}


void EnemyEntity::setPosition(sf::Vector2f position)
{
	this->model->setPosition(sf::Vector2f(position.x - (this->model->getGlobalBounds().width / 2),
	                                      position.y - (this->model->getGlobalBounds().height / 2)));
}

bool EnemyEntity::isColliding(const EnemyEntity& other) const
{
	return model->getGlobalBounds().intersects(other.model->getGlobalBounds());
}

sf::Vector2i EnemyEntity::getPosition()
{
	return sf::Vector2i(this->model->getPosition().x, this->model->getPosition().y);
	//return sf::Vector2i(this->shape.getGlobalBounds().getPosition().x, this->shape.getGlobalBounds().getPosition().y);
}

const sf::Sprite EnemyEntity::getShape() const
{
	return *this->model;
}
