#pragma once
#include "Button.h"
#include "TowerEntity.h"

class TowerSelectorElement :
	public Button
{
private:
	sf::Vector2f position;
	TowerType type;

	sf::Texture* texture;
	sf::Sprite* sprite;

public:
	TowerType getType() { return type; }
	void render(sf::RenderTarget* target);
	TowerSelectorElement(float x, float y,TowerType type,sf::Color color);
};
