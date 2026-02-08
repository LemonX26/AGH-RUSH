#pragma once
#include "Button.h"
#include "TowerEntity.h"
#include "TowerSelectorElement.h"

class TowerSelector :
    public Button
{
private :
    sf::Vector2f position;
    TowerEntity* tower;
    bool shouldShowElements;
    float damage = 10.f;
    std::vector<TowerSelectorElement*> elements;
    float damageTimer = 0.f;
    float splashDamageTimer = 0.f;
    int* money;
    EnemyEntity* target = nullptr;

    float timeShootAnimation = 0;
    void updateDamageDealt(EnemyEntity* enemyTarget, const float dt);
    int getCost();

    void initElements();
public:
    float updateSplashDamageTimer(float dt, float resetBy)
    {
        splashDamageTimer += dt;
        if (splashDamageTimer >= resetBy)
            splashDamageTimer = 0.f;
		return splashDamageTimer;
    }
    void onClick();
    void render(sf::RenderTarget* target);
    void update(const sf::Vector2f mousePos, const float& dt);

    bool isEnemyKilled();
    void setTarget(EnemyEntity* enemyTarget);

    EnemyEntity* getTarget() { return target; }
    TowerEntity* getTower() { return tower; }
    sf::Vector2f getPosition() { return position; }
    TowerSelector(float x, float y,int * money);
    ~TowerSelector();
};



