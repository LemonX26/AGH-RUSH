#pragma once
#include <SFML/Graphics/RenderTarget.hpp>

#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include "SFML/Audio.hpp"
#include "SFML/Network.hpp"

#include <fstream>
#include <sstream>

#include <stack>
#include <map>
#include <vector>
class Entity
{
private:

protected:
	bool counted;
	sf::Texture* texture;
	sf::Sprite* model;
	int id;
	const sf::Sprite getShape() const;
	
public:
	Entity();
	virtual ~Entity();
	
	// sf::Sprite getShape();
	//Functions
	virtual void move(const float& dt, const float x, const float y)=0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target)=0;
	//sf::Vector2i getPosition();
};
