#include "AdditionalAttack.h"
#include "state.h"
#include <iostream>
using namespace std;

void AdditionalAttack::updateDamage(EnemyEntity* enemyTarget)
{
	if (enemyTarget == nullptr)
		return;
	enemyTarget->takeDamage(25.f);
}

AdditionalAttack::AdditionalAttack()
{
	this->Initattack();
	//this->makeDamage();
}

AdditionalAttack::~AdditionalAttack()
{
}

void AdditionalAttack::Initattack()
{
	 //-> for class, . for sprite,vectors etc.	
	this->model->setPosition(mouse_position().x+250, mouse_position().y-500);//kordy koncoew mouse_position().x-180, mouse_position().y-185
	this->model->setTextureRect(sf::IntRect(0, 0, 60, 60));
	this->texture->loadFromFile("characters_images/fire_attack.png");
	position_x = mouse_position().x - 180;
	position_y = mouse_position().y - 185;
	//elements.push_back(new AdditionalAttackButton(this->position.x, this->position.y+700,70.f,70.f,sf::Color::Green));
}

void AdditionalAttack::StartAttack()
{
	sf::Time elapsed = clock.restart();
	float rotation = model->getRotation() + rotationSpeed * elapsed.asSeconds();
	this->model->setRotation(rotation);
	if (model->getPosition().x <= position_x && model->getPosition().y >= position_y) 
	{
		velocity.x = 0;
		rotationSpeed = 0;
		velocity.y = 0;
		counter++;
		if(counter>1)
		model->setTextureRect(sf::IntRect(0, 0, 0, 0)); 
		/*
		if (clock.getElapsedTime().asSeconds() > 0.0025) {
			model->setTextureRect(sf::IntRect(0, 0, 0, 0));
		}
		*/
	}

}

bool AdditionalAttack::makeDamage()//(bool damage
{
	//cout << model->getPosition().x << "  " << model->getPosition().y << endl;
	if (model->getPosition().x <= position_x && model->getPosition().y >= position_y) {
		return true;
		cout << true;
	}
	else
	return false;

	if (abs(model->getPosition().x - position_x) <= 40 && abs(model->getPosition().y - position_y) <= 40)//
	{
		
	}
	
}


void AdditionalAttack::render(sf::RenderTarget* target)
{
	//Button::render(target);
	target->draw(*this->model);
}

void AdditionalAttack::onClick()
{
}


void AdditionalAttack::update(const float& dt)//const sf::Vector2f mousePos,
{
	this->model->move(velocity);
	this->model->getPosition();
}

void AdditionalAttack::move(const float& dt, float x, float y)
{
	this->model->move(x * this->movementSpeed * dt, y * this->movementSpeed * dt);
}

sf::Vector2i AdditionalAttack::getPosition()
{
	return sf::Vector2i(this->model->getPosition().x, this->model->getPosition().y);
	//return sf::Vector2i(this->shape.getGlobalBounds().getPosition().x, this->shape.getGlobalBounds().getPosition().y);
}
void AdditionalAttack::setPosition(sf::Vector2f position)
{
	this->model->setPosition(sf::Vector2f(position.x - (this->model->getGlobalBounds().width / 2),
		position.y - (this->model->getGlobalBounds().height / 2)));
}

sf::Vector2f AdditionalAttack::mouse_position()
{
	return sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}

const sf::Sprite AdditionalAttack::getShape() const
{
	return *this->model;
}
