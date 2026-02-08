#include "LifeCounter.h"
#include <iostream>
LifeCounter::LifeCounter()
{
	this->InitLifeScore(0);
}

LifeCounter::~LifeCounter()
{

}

void LifeCounter::InitLifeScore(int score)
{
	sf::Font font;
	//font.loadFromFile("C:/Users/snajp/source/repos/AGH-Rush/Fonts/starjedi.ttf");
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}
	
	lifeScore.setFont(font);
	lifeScore.setCharacterSize(24);
	lifeScore.setString("CHUJ");//std::to_string(score)
	lifeScore.setFillColor(sf::Color::Black);
	lifeScore.getOutlineColor();
	std::cout << "font" << std::endl;
	
	huj.setSize(sf::Vector2f(20.f, 20.f));
	huj.setFillColor(sf::Color::Red);
	huj.setPosition(sf::Vector2f(100.f, 100.f));

}

void LifeCounter::counter(std::vector<EnemyEntity*> enemies)
{

	
}

void LifeCounter::update(const float& dt)
{
	//std::cout << "NUMBER OF ENEMIES WHO SURVIVED: " << COUNTER << "\n";
}

void LifeCounter::render(sf::RenderTarget* target)
{
	
	target->draw(huj);
}
