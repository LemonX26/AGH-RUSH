#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "State.h"
#include "AdditionalAttack.h"
class SlowingAttack:
	public Entity
{
public:

	SlowingAttack();
	~SlowingAttack();
	void SetAttackParameters();
	void AttackMechanics();
	void render(sf::RenderTarget* target) override;
	void update(const float& dt) override;
	void move(const float& dt, float x, float y) override; //zeby dziedziczyc po Entity musi miec te same funkcje   
	sf::Vector2i getPosition();
	const sf::Sprite getShape() const;
	const sf::Sprite getSize() const;
	bool isColliding(const SlowingAttack& other) const;
	sf::Clock Clock;
	sf::Time timee;
	//float Slower_Range = 100.f;
	//sf::Vector2i getPosition();
	void setPosition(sf::Vector2f position);
	Vector2f mouse_position();

};

