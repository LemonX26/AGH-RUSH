#pragma once
//#include "Button.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "State.h"
#include "AdditionalAttackButton.h"
#include "EnemyEntity.h"

//#include "TowerSelector.h"
using namespace sf;
using namespace std;
class EnemyEntity;

class AdditionalAttack:
	public Entity//, Button//TowerSelector

{
	private:
		float movementSpeed = 100.f;
		std::vector<AdditionalAttackButton*> elements;
		sf::Vector2f position;
		void updateDamage(EnemyEntity* enemyTarget);
public:
	Event event;
	AdditionalAttack();
	~AdditionalAttack();
	void Initattack();
	void StartAttack();
	bool makeDamage();//bool damage
	sf::Sprite enemy;
	vector <Sprite*> additionalAttack;
	std::vector<EnemyEntity*> enemies;
	Vector2f velocity{-4.f, 3.15f};
	void move(const float& dt, float x, float y) override;
	void update( const float& dt);//const sf::Vector2f mousePos,
	void render(sf::RenderTarget* target);
	void onClick();
	//const bool isPressed() const;
	sf::Vector2i getPosition();
	void setPosition(sf::Vector2f position);
	Vector2f mouse_position();
	EnemyEntity* target = nullptr;
	const sf::Sprite getShape() const;
	//std::vector<AdditionalAttack*> additionalAttack;
	// //
	//zeby dziedziczyc po Entity musi miec te same funkcje
	// //
	//rotation
	
	float rotationSpeed = 360.0f;
	sf::Clock clock;

	int MAX_SIZE_ATTACK_VECTOR = 1;
	int counter = 0;
	int position_x=0;
	int position_y=0;
};

