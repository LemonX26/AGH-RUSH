#pragma once
#include "EnemyEntity.h"

class EnemyEntity;

enum class TowerType
{
	Ranger,
	Artillery,
	End
};

class TowerEntity :
	public Entity
{
private:
	TowerType type;
	sf::Vector2i position;

	float towerRadius = 200.f;
	sf::Vector2i aimPoint = sf::Vector2i(0.f,0.f);
	int killedEnemys=0;
	float reloadSpeed = 1.f;

	sf::Vector2i targetPosition;

	sf::Texture* textureShoot;

	sf::CircleShape* radiusHighlighter;
	sf::CircleShape* aimPointHighlighter;
	sf::RectangleShape* aimHighlighter;

	void setPosition(float x, float y);
	void setAimPoint(float angle);

	void initRadiusHighlighter();
	void initAimPointHighlighter();
	void initAimHighlighter();
public:
	TowerEntity(sf::Vector2f position, TowerType type);
	~TowerEntity() override;
	sf::Vector2i getAimPoint(){ return aimPoint; }
	void updateRotation(sf::Vector2i targetPosition);
	float getRadius() { return towerRadius; }
	TowerType getType() { return type; }
	void render(sf::RenderTarget* target) override;
	void update(const float& dt);
	void move(const float& dt, float x, float y) override;
	void setShoot(bool isShooting);
};

