#pragma once
#include "EnemyEntity.h"
#include "TowerEntity.h"
#include "State.h"
#include "AlignToCurrentPosition.h"
#include "TowerSelector.h"
#include "SetCords.h"
#include "AdditionalAttack.h"
#include "LifeCounter.h"
#include "SlowingAttack.h"
#include <sstream>
#include "FrozenAttack.h"
#include "AdditionalAttackButton.h"


class GameState :
	public State, SetCords
{
private:
	//Variables
	float vel_x; float vel_y;float vel2_x; float vel2_y;
	float mapDt = 0.0f;
	int LIFE_COUNTER = 20;
	int numberOfWaves = 0;
	int money = 200;
	const int breakBetweenWaves = 10;
	int timeFor1Wave = 3;
	int timeLeft = timeFor1Wave;
	int score = 0;
	//background
	sf::Texture* backgroundTexture;
	sf::Texture* backgroundTexture2;
	

	sf::Sprite* background;
	//Attacks
	sf::Texture* FireAttack;
	sf::Sprite* fireAttack;

	
	sf::Font font;
	sf::Text liveBoard;
	sf::Text wavesBoard;
	sf::Text waveUpdate;
	sf::Text endGame;
	sf::Text Start;
	sf::Text moneyBoard;
	


	std::vector<EnemyEntity*> enemies;
	std::vector<sf::Vector2f> towerPositions;
	std::vector<TowerSelector*> towerSelectors;
	std::vector<TowerEntity*> towers;
	std::vector<AdditionalAttack*> additionalAttack;
	std::vector<LifeCounter*> lifeCounter;
	std::vector<SlowingAttack*> slowingAttack;
	std::vector<AdditionalAttackButton*> buttons;
	//std::map<std::string, AdditionalAttackButton*> button;
	
	//Functions
	
	void finalScore(int numberOfWaves, int LIFE_COUNTER); //add coins
	void initKeybinds() override;
	void initTowersPositions();
	void initTowersSelectors();
	void initEnemies();
	void initBackground();
	void InitFireAttack();
	void InitCounter(std::vector<EnemyEntity*> enemies, const float& dt);
	void InitSlowingAttack();
	void InitVelocityVectors();
	void UpdateSlowing(const float& dt);
	void FrozenAttack();
	void InitFonts();
	void InitText();
	void UpdateText();
	void initAdditionalAttackButton();
	void updateButton(); //(const float& dt
	void updateBackground(const float& dt);
	void updateSplashDamage();
	bool checkIfMapIsEmpty(std::vector<EnemyEntity*> enemies);
	void initWave();
	void createTower(sf::Vector2f position);
	void updateTowerRotation(std::vector<TowerSelector*> towerSelectors, const float& dt);
	void moveEnemies(std::vector<EnemyEntity*> enemies, const float& dt);
	void fire_Attack(std::vector<AdditionalAttack*> additionalAttack, const float& dt);
	void updateSplashDamage(const float& dt);
	
	int countDown(int time);


	
  //void startSLowingAttack(const float& dt);
	//void startFireAttack(const float& dt);
	

	EnemyEntity* getClosestEnemy(Vector2i aimPointPosition, sf::Vector2i towerPosition, float radius);
	
	const sf::Sprite& getShape() const;

	//booleans
	bool start_slowing_attack = false;
	bool leftButtonPressedLastFrame = false;
	bool isFireButtonActive = false;
	bool isSlowingButtonActive = false;
	bool waveState = false;
	bool start_attack = false;
	bool start_enemies_attack = false;
	bool eraseAttack = false;
	
	
	Vector2f CheckVelocity(float x, float y);
	std::vector<int> id;
	std::vector<Vector2f> moveSpeed;
	std::vector<Vector2f> moveSpeed2;
	sf::Clock clock;sf::Clock clock2;
	sf::Clock clockSlowingAttack;
	sf::Clock clockFireAttack;
//	Time elapsedAttack = clock.getElapsedTime();
public:
	GameState(sf::RenderWindow* window, std::map <std::string, int>* supportedKeys);
	~GameState() override;
	//Functions
	void endState() override;
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void updateGui();
	void render(sf::RenderTarget* target = nullptr) override;
	void renderGui(sf::RenderTarget* target);
	
	
	
};
