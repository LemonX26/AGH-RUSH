#include "TowerSelector.h"

#include <iostream>

void TowerSelector::updateDamageDealt(EnemyEntity* enemyTarget, const float dt)
{
	if (enemyTarget == nullptr || this->getTower()->getType() == TowerType::Artillery)
		//artillery is implemented in gamestate->updateSplashDamage
		return;
	enemyTarget->takeDamage(this->damage);
}

int TowerSelector::getCost()
{
	if (this->getTower() == nullptr)
		return 0;
	switch (this->getTower()->getType())
	{
	case TowerType::Artillery:
		return 100;
	default:
		return 70;
	}
}

void TowerSelector::initElements()
{
	for (int i = 0; i < static_cast<int>(TowerType::End); i++)
	{
		sf::Color color;
		switch (static_cast<TowerType>(i))
		{
		case TowerType::Ranger:
			color = sf::Color::Green;
			break;
		case TowerType::Artillery:
			color = sf::Color::Blue;
			break;
		}

		this->elements.push_back(new TowerSelectorElement(
			this->position.x + (i * 60 - static_cast<int>(TowerType::End) * 50 / 2) + 40, this->position.y - 40,
			static_cast<TowerType>(i), color));
	}
}

void TowerSelector::onClick()
{
	if (this->tower == nullptr)
	{
		//this->tower = new TowerEntity(this->position, TowerType::Ranger);
		std::cout << "Creating tower at: " << this->position.x << ", " << this->position.y << std::endl;
		this->shouldShowElements = true;
	}
}

void TowerSelector::render(sf::RenderTarget* target)
{
	Button::render(target);
	if (this->tower != nullptr)
		this->tower->render(target);
	else if (this->shouldShowElements)
		for (auto& e : this->elements)
			e->render(target);
}

void TowerSelector::update(const sf::Vector2f mousePos, const float& dt)
{
	Button::update(mousePos);
	for (auto& e : this->elements)
	{
		if (this->shouldShowElements)
		{
			e->update(mousePos);
			if (e->isPressed())
			{
				this->tower = new TowerEntity(this->position, e->getType());
				if (*money - this->getCost() < 0)
				{
					this->tower = nullptr;
					return;
				}
				*money -= this->getCost();
				this->shouldShowElements = false;
			}
		}
	}
	if (this->tower != nullptr)
	{
		this->tower->update(dt);
		if (this->target != nullptr)
			this->tower->updateRotation(this->target->getPosition());
		if (this->damageTimer < 1.f)
		{
			this->damageTimer += dt;
		}
		else
		{
			this->damageTimer = 0.f;
			this->updateDamageDealt(this->target, dt);
		}
		if (this->target != nullptr && this->tower->getType() != TowerType::Artillery)
		{
			if (damageTimer < 0.5f)
			{
				this->tower->setShoot(true);
			}
			else
			{
				this->tower->setShoot(false);
			}
		}
		else
		{
			this->tower->setShoot(false);
		}
	}
}

bool TowerSelector::isEnemyKilled()
{
	if (this->target != nullptr)
	{
		if (!this->target->isAlive)
		{
			this->target = nullptr;
			return true;
		}
	}
	return false;
}

void TowerSelector::setTarget(EnemyEntity* enemyTarget)
{
	this->target = enemyTarget;
}


TowerSelector::TowerSelector(float x, float y, int* money):
	Button(x - 25, y - 25, 50, 50, nullptr, "", sf::Color::Transparent, sf::Color(200, 200, 200, 100),
	       sf::Color(200, 10, 200, 200)), tower(nullptr)
{
	this->position = sf::Vector2f(x - 25, y - 25);
	this->shouldShowElements = false;
	this->initElements();
	this->money = money;
}

TowerSelector::~TowerSelector()
{
	delete this->tower;
}
