#include "LifeCounter2.h"
#include "state.h"
#include <iostream>

LifeCounter2::LifeCounter2()
{
	this->SetAttackParameters();
}

LifeCounter2::~LifeCounter2()
{
}

void LifeCounter2::SetAttackParameters()
{
	this->model->setTextureRect(sf::IntRect(0, 0, 60, 60));
	this->model->setPosition(sf::Vector2f(150.f, 150.f));
	this->model->setColor(sf::Color::Blue);
}

void LifeCounter2::render(sf::RenderTarget* target)
{
	target->draw(*this->model);
}

void LifeCounter2::update(const float& dt)
{
}
