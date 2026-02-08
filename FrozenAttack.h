#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "AdditionalAttack.h"
class FrozenAttack:
	public Entity
{
private:
	sf::RectangleShape frozenAttack;
	void InitShape();

public:
	FrozenAttack(float x,float y);
	~FrozenAttack();
	const sf::Sprite& getShape() const;
	void render(sf::RenderTarget* target) override;
	void update(const float& dt) override;
	void move(const float& dt, float x, float y) override; //zeby dziedziczyc po Entity musi miec te same funkcje  
};

