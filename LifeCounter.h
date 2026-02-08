#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "EnemyEntity.h"
class LifeCounter:
	public  EnemyEntity

{

	
public:
	LifeCounter();
	std::vector<EnemyEntity*> enemies;
	~LifeCounter();
	sf::Text lifeScore;
	void InitLifeScore(int score);
	void dupa();
	void counter(std::vector<EnemyEntity*> enemies);
	int COUNTER=0;
	//FINAL CORDS
	sf::RectangleShape huj;
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	int final_cord_x = 0 ;
	
};

