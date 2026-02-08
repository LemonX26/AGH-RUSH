#pragma once
#include "Entity.h"
class EnemyEntity :
    public Entity
{
private:
    sf::Texture* aliveTexture;
    sf::Texture* deadTexture;
    float hp=100.f;
    float movementSpeed = 100.f;
    bool isSlowed = false;
    bool isGiveDamage = false;
    float slowMultiplier = 0.6f;
    float givenDamage = 55.f;
    sf::Font *font;
    sf::Text *hpText;
   void initHpText();
public:
    EnemyEntity();
    ~EnemyEntity();
	void move(const float& dt, const float x, const float y);
    void updateSlowMultiplier(float multiplier);
    void setSlowed(bool slowed);
    void updateGetDamage(float givendamage);
    bool checkIsEnemyAlive(bool isalive);
    void getDamage(bool damage);
	void update(const float& dt);
    void updateHpText();
    bool endOfWave();//std::vector<Entity*> entities,Entity* target
    // std::vector<Entity*> entity;
    bool isAlive = true;
    void takeDamage(float damage);
    sf::Vector2f mouse_position();
    void render(sf::RenderTarget* target);
    void setPosition(sf::Vector2f position);
    bool isColliding(const EnemyEntity& other) const;
     sf::Vector2i getPosition();
     Entity* target;
     const sf::Sprite getShape() const;

};

