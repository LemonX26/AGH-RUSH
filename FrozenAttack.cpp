#include "FrozenAttack.h"

FrozenAttack::FrozenAttack(float x, float y)
{
	this->model->setPosition(x, y);
	this->InitShape();
}

FrozenAttack::~FrozenAttack()
{
}

const sf::Sprite& FrozenAttack::getShape() const
{
	return *this->model;
	// TODO: tu wstawiæ instrukcjê return
}

void FrozenAttack::InitShape()
{
	this->model->setColor(sf::Color::Yellow);
}

void FrozenAttack::render(sf::RenderTarget* target)
{
	target->draw(*this->model);
}

void FrozenAttack::update(const float& dt)
{
}

void FrozenAttack::move(const float& dt, float x, float y)
{
}
