#include "SlowingAttack.h"
#include "state.h"
#include <iostream>

SlowingAttack::SlowingAttack()
{
	this->SetAttackParameters();
	this->AttackMechanics();
}

SlowingAttack::~SlowingAttack()
{
}

void SlowingAttack::SetAttackParameters()
{

	this->model->setPosition(mouse_position().x-205 , mouse_position().y - 140);
	this->texture->loadFromFile("characters_images/slowAttack.png");
	this->model->setTexture(*this->texture);
	this->model->setTextureRect(sf::IntRect(0, 0, 78, 78));
	this->model->setColor(sf::Color(255, 255, 255, 128));
	std::cout << "Slowing Attack Created" << "\n";

}

void SlowingAttack::AttackMechanics()
{
	timee = Clock.getElapsedTime();
	std::cout << timee.asSeconds() << endl;
	
	if (timee.asSeconds() > 0.0025) {
		cout << "end of attack" << endl;
		Clock.restart();
	}
	//this->model->setPosition(mouse_position().x - 205, mouse_position().y - 140);
	
}

void SlowingAttack::render(sf::RenderTarget* target)
{
	target->draw(*this->model);
}

void SlowingAttack::update(const float& dt)
{
}

void SlowingAttack::move(const float& dt, float x, float y)
{
}

sf::Vector2i SlowingAttack::getPosition()
{
	return sf::Vector2i(this->model->getPosition().x, this->model->getPosition().y);
}

const sf::Sprite SlowingAttack::getShape() const
{
	return *this->model;
}

bool SlowingAttack::isColliding(const SlowingAttack& other) const
{
	return this->model->getGlobalBounds().intersects(other.model->getGlobalBounds());
}

void SlowingAttack::setPosition(sf::Vector2f position)
{
	this->model->setPosition(sf::Vector2f(position.x - (this->model->getGlobalBounds().width / 2),
		position.y - (this->model->getGlobalBounds().height / 2)));
}

Vector2f SlowingAttack::mouse_position()
{
	return sf::Vector2f(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
}


