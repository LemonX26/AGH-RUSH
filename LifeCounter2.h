#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "State.h"
class LifeCounter2 :
	public Entity
{
public:

	LifeCounter2();
	~LifeCounter2();
	void SetAttackParameters();
	void render(sf::RenderTarget* target) override;
	void update(const float& dt) override;

};

