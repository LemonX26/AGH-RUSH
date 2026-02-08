#include <iostream>
#include <algorithm>
#include "GameState.h"
#include <chrono>
#include <thread>

void GameState::initKeybinds()
{
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void GameState::InitVelocityVectors()
{
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		this->moveSpeed.push_back(Vector2f());
		this->moveSpeed2.push_back(Vector2f());
	}
	
}

void GameState::finalScore(int numberOfWaves, int LIFE_COUNTER)
{
	
	score = (numberOfWaves * 50 + 1.5 * LIFE_COUNTER)*2;  // * coins
	cout << score << endl;
}

bool GameState::checkIfMapIsEmpty(std::vector<EnemyEntity*> enemies)
{
	bool check = false;
	for (auto& enemy : enemies)
	{
		if (!enemy->endOfWave())
		{
			check = false;
			return false;
		}
		check = true;
	}
	if (check)
		return true;
}

void GameState::initWave()
{		
	//countDown();
	Time elapsed = clock.getElapsedTime();	
	Time elapsed1Sec = clock2.getElapsedTime();
	if (timeLeft > 1)
		if (elapsed1Sec.asSeconds() > 1)
		{
			timeLeft--;
			clock2.restart();
		}
	if (numberOfWaves == 0 && elapsed.asSeconds() > timeFor1Wave)
		numberOfWaves = 1;

	if (numberOfWaves < 7&& numberOfWaves>0)
	{
		if (checkIfMapIsEmpty(this->enemies) && !waveState && this->enemies.empty())
		{
			for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
			{
				this->id.push_back(i);
				this->enemies.push_back(new EnemyEntity());
				this->enemies[i]->setPosition(get_Random_Cord());
			}
			cout << NUMBER_OF_ENEMIES << endl;
			waveState = true;
			
			cout << "Wave: " << numberOfWaves << endl;
		}

		else if (waveState && checkIfMapIsEmpty(this->enemies)) //get ready
		{
			timeLeft = breakBetweenWaves;
			clock.restart();
			elapsed = clock.getElapsedTime();
			waveState = false;
			for (auto& enemy : enemies)
				if (!enemy->isAlive)
					money += 8;
			cout << "enemies.size(): " << enemies.size() << endl;
			cout << "NUMBER_OF_ENEMIES: " << NUMBER_OF_ENEMIES << endl;
			if (timeLeft > 0)
				if (elapsed1Sec.asSeconds() > 1)
				{
					timeLeft--;
					clock2.restart();
				}
		}
		else if (checkIfMapIsEmpty(this->enemies) && enemies.size() == NUMBER_OF_ENEMIES && elapsed.asSeconds() > breakBetweenWaves)
		{
			NUMBER_OF_ENEMIES++;
			this->enemies.clear();
			numberOfWaves++;
			waveState = false;
			clock.restart();
		}
		else if (LIFE_COUNTER == 0) 
		{
			NUMBER_OF_ENEMIES = 0;
			this->enemies.clear();
		}
	}
}

void GameState::initEnemies()
{
	srand(time(nullptr));
	for (int i = 0; i < NUMBER_OF_ENEMIES; i++)
	{
		this->id.push_back(i);
	
	}
}

void GameState::initTowersPositions()
{
	std::vector<Vector2f> rawPositions;
	rawPositions.push_back(Vector2f(1030.f, 168.f));
	rawPositions.push_back(Vector2f(439.f, 400.f));
	rawPositions.push_back(Vector2f(786.f, 327.f));
	rawPositions.push_back(Vector2f(1240.f, 364.f));
	rawPositions.push_back(Vector2f(654.f, 684.f));
	rawPositions.push_back(Vector2f(1218.f, 744.f));
	rawPositions.push_back(Vector2f(826.f, 918.f));
	rawPositions.push_back(Vector2f(1485.f, 955.f));
	rawPositions.push_back(Vector2f(222.f, 655.f));

	for (Vector2f raw_position : rawPositions)
	{
		this->towerPositions.push_back(alignToCurrentPosition(this->window, raw_position));
	}
}

void GameState::initTowersSelectors()
{
	for (Vector2f position : this->towerPositions)
	{
		this->towerSelectors.push_back(new TowerSelector(position.x, position.y, &money));
	}
}

void GameState::initBackground()
{
	this->backgroundTexture = new Texture;
	backgroundTexture->loadFromFile("Maps/mapa.png");
	this->backgroundTexture2 = new Texture;
	backgroundTexture2->loadFromFile("Maps/mapa2.png");
	this->background = new Sprite(*backgroundTexture, IntRect(0, 0, 1920, 1080));
	this->background->setScale(this->window->getSize().x / 1920.f, this->window->getSize().y / 1080.f);
}

void GameState::initAdditionalAttackButton()
{
	this->buttons.push_back(new AdditionalAttackButton(20.f, 838.f, 90.f, 90.f, Color::Blue));
	this->buttons.push_back(new AdditionalAttackButton(20.f + 100.f, 838.f, 90.f, 90.f, Color::Red));
}

void GameState::updateButton() //const float& dt
{
	Time elapsedSlowingAttack = clockSlowingAttack.getElapsedTime();
	Time elapsedFireAttack = clockFireAttack.getElapsedTime();

	if (elapsedSlowingAttack.asSeconds() > (breakBetweenWaves * 0.6)|| isSlowingButtonActive)
		buttons[0]->setEnabled(true);
	else
		buttons[0]->setEnabled(false);


	if (elapsedFireAttack.asSeconds() > (breakBetweenWaves * 0.8)|| isFireButtonActive)
		buttons[1]->setEnabled(true);
	else
		buttons[1]->setEnabled(false);



	if (buttons[0]->isPressed() && elapsedSlowingAttack.asSeconds() > (breakBetweenWaves * 0.6))
	{
		clockSlowingAttack.restart();
		isSlowingButtonActive = true;
	}

	if (buttons[1]->isPressed() && elapsedFireAttack.asSeconds() > (breakBetweenWaves * 0.8))
	{
		clockFireAttack.restart();
		isFireButtonActive = true;
	}
}

void GameState::updateBackground(const float& dt)
{
	this->mapDt += dt;
	if (mapDt > 0.5)
	{
		if (this->background->getTexture() == backgroundTexture2)
			this->background->setTexture(*backgroundTexture);
		else
			this->background->setTexture(*backgroundTexture2);
		mapDt = 0;
	}
}

void GameState::updateSplashDamage(const float& dt)
{
	for (auto& towerSelector : towerSelectors)
	{

		if (towerSelector->getTower() == nullptr || towerSelector->getTarget() == nullptr)
			continue;
		if (towerSelector->getTower()->getType() != TowerType::Artillery)
			continue;
		auto towerEnemyBounds = towerSelector->getTarget()->getShape().getGlobalBounds();
		towerEnemyBounds.top -= 10;
		towerEnemyBounds.left -= 10;
		towerEnemyBounds.width += 20;
		towerEnemyBounds.height += 20;
		float timer = towerSelector->updateSplashDamageTimer(dt, 3);
		if (timer == 0.f) {
			for (auto& enemy : enemies)
			{
				if (!enemy->isAlive)
					continue;

				if (towerEnemyBounds.intersects(enemy->getShape().getGlobalBounds()))
				{
					enemy->takeDamage(25);
				}
			}
		}
	}
}


void GameState::InitFireAttack()
{
	if (additionalAttack.size() < 1)
	{
		this->additionalAttack.push_back(new AdditionalAttack());
	}
	else if (additionalAttack.size() == 1)
	{
		this->additionalAttack.erase(additionalAttack.begin());
	}
}

// Attacks
void GameState::fire_Attack(std::vector<AdditionalAttack*> additionalAttack, const float& dt)
{
	bool leftButtonPressed = Mouse::isButtonPressed(Mouse::Right);
	if (isFireButtonActive && (leftButtonPressed && !leftButtonPressedLastFrame))
	{
		InitFireAttack();
		start_attack = true;
		isFireButtonActive = false;
	}
	if (start_attack)
	{
		for (auto& fireattack : additionalAttack)
		{
			for (size_t i = 0; i < enemies.size(); i++)
			{
				if (fireattack->getShape().getGlobalBounds().intersects(this->enemies[i]->getShape().getGlobalBounds()))
				//true
				{
					if (fireattack->makeDamage())
						enemies[i]->getDamage(true);
					else
						enemies[i]->getDamage(false);
				}
			}
		}
	}


	for (auto& attack : additionalAttack)
	{
		attack->StartAttack();
	}
	if (additionalAttack.size() == 0 && start_attack)
	{
		InitFireAttack();
	}
}

void GameState::FrozenAttack()
{
	bool leftButtonPressed = Mouse::isButtonPressed(Mouse::Right);

	Time elapsed = clock.getElapsedTime();
	if (isSlowingButtonActive && (leftButtonPressed && !leftButtonPressedLastFrame) && Event::MouseButtonReleased) //
	{
		clock.restart();
		InitSlowingAttack();
		isSlowingButtonActive = false;
		eraseAttack = true;
		elapsed = clock.getElapsedTime();
	}
	if (elapsed.asSeconds() > 5 && eraseAttack)
	{
		this->slowingAttack.erase(slowingAttack.begin());
		clock.restart();
		eraseAttack = false;
	}
}



void GameState::InitCounter(std::vector<EnemyEntity*> enemies, const float& dt)
{

	for (auto& enemy : enemies)
	{
		if ((enemy->getPosition().x) == 0.f && enemy->checkIsEnemyAlive(enemy->isAlive)) //!lives&&
		{
			sleep(milliseconds(30));
			LIFE_COUNTER--;
		}
	}

}

void GameState::InitSlowingAttack()
{
	if (slowingAttack.size() < 1)
	{
		this->slowingAttack.push_back(new SlowingAttack());
	}
	else if (slowingAttack.size() == 1)
	{
		this->slowingAttack.erase(slowingAttack.begin());
		this->slowingAttack.push_back(new SlowingAttack());
	}
}

EnemyEntity* GameState::getClosestEnemy(Vector2i aimPointPosition, Vector2i towerPosition, float radius)
{
	EnemyEntity* closestEnemy = nullptr;
	for (EnemyEntity* enemy : this->enemies)
	{
		// find first alive enemy
		if (enemy->isAlive)
		{
			closestEnemy = enemy;
			break;
		}
	}
	if (closestEnemy != nullptr)
	{
		for (EnemyEntity* enemy : this->enemies)
		{
			if (getDistance(enemy->getPosition(), towerPosition) > radius)
				continue;
			if (!enemy->isAlive)
				continue;
			double closestDistance = getDistance(closestEnemy->getPosition(), aimPointPosition);
			double distance = getDistance(enemy->getPosition(), aimPointPosition);
			if (distance < closestDistance)
			{
				closestEnemy = enemy;
			}
		}
		if (getDistance(closestEnemy->getPosition(), towerPosition) > radius) // final check
			return nullptr;
	}
	return closestEnemy;
}

void GameState::UpdateSlowing(const float& dt)
{
	for (auto& slowingattack : slowingAttack)
	{
		for (size_t i = 0; i < enemies.size(); i++)
		{
			if (slowingattack->getShape().getGlobalBounds().intersects(this->enemies[i]->getShape().getGlobalBounds()))
			{
				if (id[i] < 1000)
				{
					id[i] = id[i] + 1000;
					enemies[i]->setSlowed(true);
				}
			}
			else
			{
				id[i] = i;
				enemies[i]->setSlowed(false);
			}
		}
	}
}


Vector2f GameState::CheckVelocity(float x, float y)
{
	cout << x << " " << y << endl;
	return Vector2f{x, y};
}

void GameState::InitFonts()
{
	if (!this->font.loadFromFile("Fonts/Comfortaa-VariableFont_wght.ttf"))
	{
		std::cout << "ERROR NIE POBRALO" << endl;
	}
}

void GameState::InitText()
{
	//this->liveBoard
	this->liveBoard.setFont(this->font);
	this->liveBoard.setCharacterSize(18);
	this->liveBoard.setFillColor(Color::White);
	this->liveBoard.setStyle(Text::Bold);

	this->wavesBoard.setFont(this->font);
	this->wavesBoard.setCharacterSize(18);
	this->wavesBoard.setFillColor(Color::White);
	this->wavesBoard.setPosition(sf::Vector2f(100, 0));
	this->wavesBoard.setStyle(sf::Text::Bold);

	this->waveUpdate.setFont(this->font);
	this->waveUpdate.setCharacterSize(40);
	this->waveUpdate.setFillColor(Color::White);
	this->waveUpdate.setPosition(sf::Vector2f(600, 350));
	this->waveUpdate.setStyle(sf::Text::Bold);

	this->endGame.setFont(this->font);
	this->endGame.setCharacterSize(40);
	this->endGame.setFillColor(Color::White);
	this->endGame.setPosition(sf::Vector2f(500, 350));
	this->endGame.setStyle(sf::Text::Bold);

	this->Start.setFont(this->font);
	this->Start.setCharacterSize(40);
	this->Start.setFillColor(Color::White);
	this->Start.setPosition(sf::Vector2f(500, 400));
	this->Start.setStyle(sf::Text::Bold);

	this->moneyBoard.setFont(this->font);
	this->moneyBoard.setCharacterSize(18);
	this->moneyBoard.setFillColor(Color::White);
	this->moneyBoard.setPosition(Vector2f(0, 30));
	this->moneyBoard.setStyle(Text::Bold);
}

void GameState::UpdateText()
{
}


void GameState::updateTowerRotation(std::vector<TowerSelector*> towerSelectors, const float& dt)
{
	for (TowerSelector* towerSelector : towerSelectors)
	{
		towerSelector->update(this->mousePosView, dt);

		if (towerSelector->getTower() != nullptr)
		{
			Vector2i aimPoint = towerSelector->getTower()->getAimPoint();
			float radius = towerSelector->getTower()->getRadius();

			EnemyEntity* currentTarget = towerSelector->getTarget();
			auto towerPosition = Vector2i(towerSelector->getPosition());
			EnemyEntity* closestEnemy = getClosestEnemy(aimPoint, towerPosition, radius);

			if ((closestEnemy == nullptr))
				towerSelector->setTarget(nullptr);
			else
			{
				if (currentTarget != closestEnemy)
					towerSelector->setTarget(closestEnemy);
			}
		}
	}
}

void GameState::moveEnemies(std::vector<EnemyEntity*> enemies, const float& dt)
{
	if (moveSpeed.size() < NUMBER_OF_ENEMIES)
		for (int i = 0; i < NUMBER_OF_ENEMIES - moveSpeed.size() + 1; i++)
		{
			this->moveSpeed.push_back(Vector2f());
			this->moveSpeed2.push_back(Vector2f());
		}

	checkIfMapIsEmpty(this->enemies);
	for (size_t i = 0; i < enemies.size(); i++)
	{
		moveSpeed[i].x = 0.f;
		moveSpeed[i].y = 0.5f;

		moveSpeed2[i].x = -0.25f;
		moveSpeed2[i].y = -1.f;


		//cout << "Enemy nr: " << i << " Velocity x: " << moveSpeed[i].x << " Velocity y: " << moveSpeed[i].y << endl;
		if (enemies[i]->getPosition().y <= 400) //&& !isActive &&id[i]<1000 //&& id[i] != (1000 + i)		
		{
		
			if (id[i] != (1000 + i))
			{
				enemies[i]->setSlowed(false);
			}
			if (id[i] == (1000 + i))
			{
				enemies[i]->setSlowed(true);
			}
			if (!eraseAttack)
				enemies[i]->setSlowed(false);
			// vel = CheckVelocity(moveSpeed[i].x, moveSpeed[i].y);
			if (enemies[i]->getPosition().y > 130 && enemies[i]->getPosition().y < 230 && enemies[i]->getPosition()
				.x > 770) //1&& id[i] != (1000 + i
			{
				//cout << "1" << endl;

				moveSpeed[i].x = -0.7f;
				moveSpeed[i].y = 0.35f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}
			else if (enemies[i]->getPosition().y >= 230 && enemies[i]->getPosition().x >= 775) // && id[i] != (1000 + i)
			//2
			{
				//cout << "2" << endl;
				moveSpeed[i].x = -0.8f;
				moveSpeed[i].y = -0.25f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}
			else if (enemies[i]->getPosition().y <= 230 && enemies[i]->getPosition().x >= 520 && enemies[i]->
				getPosition().x <= 775)
			{
				//	cout << "3" << endl;
				moveSpeed[i].x = -0.8f;
				moveSpeed[i].y = -0.4f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}

			else if (enemies[i]->getPosition().y <= 130 && enemies[i]->getPosition().x < 520) //4
			{
				//cout << "4" << endl;
				moveSpeed[i].x = -0.4f;
				moveSpeed[i].y = 0.3f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}

			else if (enemies[i]->getPosition().y >= 130 && enemies[i]->getPosition().y <= 215 && enemies[i]->
				getPosition().x >= 430 && enemies[i]->getPosition().x <= 490)
			{
				//cout << "5" << endl;
				//cout << "dupa" << endl;
				//moveSpeed.y = -10.f;

				moveSpeed[i].x = -0.2f;
				moveSpeed[i].y = 0.55f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}

			else if (enemies[i]->getPosition().y >= 215 && enemies[i]->getPosition().y <= 265)
			{
				//	cout << "6" << endl;			

				moveSpeed[i].x = 0.52f;
				moveSpeed[i].y = 0.35f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}

			else if (enemies[i]->getPosition().x <= 360 && enemies[i]->getPosition().y >= 265 && enemies[i]->
				getPosition().y <= 310)
			{
				//enemy->getPosition().x <= 360 &&
				//cout << "7" << endl;
				moveSpeed[i].x = -0.45f;
				moveSpeed[i].y = 0.45f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}

			else if (enemies[i]->getPosition().y >= 310 && enemies[i]->getPosition().y <= 395)
			{
				//cout << "8" << endl;
				moveSpeed[i].y = 0.28f;
				moveSpeed[i].x = -0.28f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}

			else if (enemies[i]->getPosition().y >= 395 && enemies[i]->getPosition().y < 400)
			{
				moveSpeed[i].y = 0.01f;
				moveSpeed[i].x = -0.7f;
				vel_x = moveSpeed[i].x;
				vel_y = moveSpeed[i].y;
			}
			enemies[i]->move(dt, moveSpeed[i].x, moveSpeed[i].y);
			vel_x = moveSpeed[i].x;
			vel_y = moveSpeed[i].y;
		}

		else
		{
			//kordy startowe 1100, 1000, 700,750	
			if (enemies[i]->getPosition().y >= 400)
			{
				if (id[i] != (1000 + i))
					enemies[i]->setSlowed(false);

				if (id[i] == (1000 + i))
				{
					enemies[i]->setSlowed(true);
				}
				if (!eraseAttack)
					enemies[i]->setSlowed(false);
				if (enemies[i]->getPosition().y <= 730 && enemies[i]->getPosition().y >= 560 && enemies[i]->
					getPosition().x >= 1300)
				{
					//cout << "1" << endl;
					moveSpeed2[i].x = -0.8f;
					moveSpeed2[i].y = -0.25f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}

				else if (enemies[i]->getPosition().y <= 740 && enemies[i]->getPosition().x <= 1300 && enemies[i]->
					getPosition().x > 900)
				{
					//cout << "267" << endl;
					moveSpeed2[i].x = -0.8f;
					moveSpeed2[i].y = 0.16f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}

				else if (enemies[i]->getPosition().y >= 570 && enemies[i]->getPosition().x <= 900 && enemies[i]->
					getPosition().x >= 630)
				{
					//cout << "367" << endl;
					moveSpeed2[i].x = -0.6f;
					moveSpeed2[i].y = -0.18f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}
				else if (enemies[i]->getPosition().y <= 660 && enemies[i]->getPosition().y >= 540 && enemies[i]->
					getPosition().x >= 360 && enemies[i]->getPosition().x <= 630)
				{
					//cout << "467" << endl;
					moveSpeed2[i].x = -0.6f;
					moveSpeed2[i].y = 0.22f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}
				else if (enemies[i]->getPosition().y >= 580 && enemies[i]->getPosition().x <= 390)
				{
					//cout << "567" << endl;

					moveSpeed2[i].y = -0.45f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}
				else if (enemies[i]->getPosition().y >= 440 && enemies[i]->getPosition().y <= 580 && enemies[i]->
					getPosition().x >= 150 && enemies[i]->getPosition().x <= 450)
				{
					//cout << "667" << endl;
					moveSpeed2[i].x = 0.8f;
					moveSpeed2[i].y = -0.7f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}
				else if (enemies[i]->getPosition().y <= 440 && enemies[i]->getPosition().y > 420 && enemies[i]->
					getPosition().x <= 450)
				{
					//cout << "767" << endl;
					moveSpeed2[i].x = -0.8f;
					moveSpeed2[i].y = -0.4f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}
				else if (enemies[i]->getPosition().y <= 420 && enemies[i]->getPosition().y > 400)
				{
					//cout << "867" << endl;
					moveSpeed2[i].x = -0.8f;
					moveSpeed2[i].y = -0.1f;
					vel2_x = moveSpeed2[i].x;
					vel2_y = moveSpeed2[i].y;
				}

				enemies[i]->move(dt, moveSpeed2[i].x, moveSpeed2[i].y);
				vel2_x = moveSpeed2[i].x;
				vel2_y = moveSpeed2[i].y;
			}
		}
	}
}

GameState::GameState(RenderWindow* window, std::map<std::string, int>* supportedKeys): State(window, supportedKeys)
{
	this->initKeybinds();
	this->initTowersPositions();
	this->initTowersSelectors();
	//this->initWave();
	//	this->initEnemies();
	this->InitVelocityVectors();
	this->initBackground();
	this->InitFonts();
	this->InitText();
	this->initAdditionalAttackButton();
	//this->waveUpdate();
}

GameState::~GameState()
{
	for (EnemyEntity* i : this->enemies)
	{
		delete i;
	}
}

void GameState::endState()
{
	std::cout << "Ending GameState!" << std::endl;
}

void GameState::updateInput(const float& dt)
{
	this->checkForQuit();
	this->moveEnemies(this->enemies, dt);
	this->InitCounter(this->enemies, dt);
	this->updateButton();
	this->fire_Attack(this->additionalAttack, dt);
	this->FrozenAttack();
	this->waveState;

	//Player Input
	/*
	if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->keybinds.at("MOVE_LEFT"))))
		this->moveEnemies(this->enemies, dt, -1.f, 0);
	if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->keybinds.at("MOVE_RIGHT"))))
		this->moveEnemies(this->enemies, dt, 1.f, 0);
	if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->keybinds.at("MOVE_UP"))))
		this->moveEnemies(this->enemies, dt, 0, -1.f);
	if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(this->keybinds.at("MOVE_DOWN"))))
		this->moveEnemies(this->enemies, dt, 0, 1.f);*/
}

void GameState::renderGui(RenderTarget* target)
{
	target->draw(this->liveBoard);
	target->draw(this->wavesBoard);
	target->draw(this->waveUpdate);
	target->draw(this->endGame);
	target->draw(this->Start);
  target->draw(this->moneyBoard);
}

int GameState::countDown(int time)
{
	Time elapsed1Sec = clock2.getElapsedTime();
	if (time > 0)
		if (elapsed1Sec.asSeconds() > 1)
		{
			time--;
			clock2.restart();
		}

	return time;
}

void GameState::updateGui()
{
	std::stringstream start;
	std::stringstream lives;
	std::stringstream waves;
	std::stringstream waveUpdates;
	std::stringstream endgame;
	Time elapsed = clock.getElapsedTime();

	lives << "LIVES: " << this->LIFE_COUNTER;
	this->liveBoard.setString(lives.str());
	waves << "WAVE: " << this->numberOfWaves << "/7\t";
	this->wavesBoard.setString(waves.str());
this->moneyBoard.setString("MONEY: " + std::to_string(this->money));

	if (!waveState&& numberOfWaves>=1&& LIFE_COUNTER!=0)
	{
	
		if(timeLeft==0)
		{ 
		waveUpdates << "NEXT WAVE IN: ";
		this->waveUpdate.setString(waveUpdates.str());
		}
		else {
			waveUpdates << "NEXT WAVE IN: " << timeLeft;
			this->waveUpdate.setString(waveUpdates.str());
		}
	}
	else if (waveState)
	{
		waveUpdates << "";
		this->waveUpdate.setString(waveUpdates.str());
	}
	if (LIFE_COUNTER == 0)
	{
		endgame << "\tGAME OVER\nYOUR FINAL SCORE: " << score;
		this->endGame.setString(endgame.str());
	}
	if (numberOfWaves == 0) 
	{
		start << "YOUR GAME WILL START IN: "<<timeLeft;
		this->Start.setString(start.str());
		if (timeLeft == 0)
		{
			waveUpdates << "YOUR GAME WILL START IN: ";
			this->waveUpdate.setString(waveUpdates.str());
		}
	}
	else
	{
		start << "";
		this->Start.setString(start.str());
	}
}

void GameState::update(const float& dt)
{
	//this->stopAttack(this->slowingAttack);
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateGui();
	//this->FrozenAttack();
	//	this->moveSpeed;
	this->updateButton();
	this->UpdateSlowing(dt);
	this->updateTowerRotation(this->towerSelectors, dt);
	this->updateBackground(dt);
	//this->waveUpdate();
	this->initWave();
	this->waveState;
	this->updateSplashDamage(dt);
	this->finalScore(this-> numberOfWaves, this-> LIFE_COUNTER); //this->coins
	


	for (LifeCounter* lives : lifeCounter)
	{
		lives->update(dt);
	}
	for (EnemyEntity* enemy : enemies)
	{
		enemy->update(dt);
	}
	for (AdditionalAttack* attack : additionalAttack)
	{
		attack->update(dt); //this->mousePosView,
	}
	for (SlowingAttack* slowingattack : slowingAttack)
	{
		slowingattack->update(dt);
	}

	for (TowerSelector* towerSelector : towerSelectors)
	{
		towerSelector->update(this->mousePosView, dt);
		if (towerSelector->isPressed())
		{
			towerSelector->onClick();
		}
	}
	for (AdditionalAttackButton* btn : buttons)
	{
		btn->update(this->mousePosView);
		if (btn->isPressed())
		{
			btn->onClick();
		}
	}
	//this->player.update(dt);
}


void GameState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;
	target->draw(*(this->background));
	//this->FrozenAttack.render(this->window);
	//
	for (EnemyEntity* enemy : enemies)
		enemy->render(target);

	for (TowerSelector* towerSelector : towerSelectors)
	{
		towerSelector->render(target);
	}
	for (AdditionalAttack* attack : additionalAttack)
	{
		attack->render(target);
	}
	for (SlowingAttack* slowingattack : slowingAttack)
	{
		slowingattack->render(target);
	}

	for (AdditionalAttackButton* btn : buttons)
	{
		btn->render(target);
	}

	//this->button->render->target;
	this->renderGui(this->window);
}
