#include "MainMenuState.h"

#include <iostream>

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Comfortaa-VariableFont_wght.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initKeybinds()
{
	this->keybinds["MOVE_LEFT"] = this->supportedKeys->at("A");
	this->keybinds["MOVE_RIGHT"] = this->supportedKeys->at("D");
	this->keybinds["MOVE_UP"] = this->supportedKeys->at("W");
	this->keybinds["MOVE_DOWN"] = this->supportedKeys->at("S");
	this->keybinds["CLOSE"] = this->supportedKeys->at("Escape");
}

void MainMenuState::initButtons()
{
	std::map<string, string> buttonLabels;
	buttonLabels["4.GAME_STATE"] = "New Game";
	buttonLabels["3.SETTINGS_STATE"] = "Settings";
	buttonLabels["2.CREDITS_STATE"] = "Credits";
	buttonLabels["1.EXIT_STATE"] = "Quit";
	int i = 0;
	for (auto buttonLabel : buttonLabels)
	{
		Vector2i buttonMiddleCoords = getButtonMiddleCoors(this->window->getSize(), 150, 50, 0, i++,
		                                                   buttons.size() - 1);
		this->buttons[buttonLabel.first] = new Button(buttonMiddleCoords.x, buttonMiddleCoords.y, 150, 50,
		                                              &this->font, buttonLabel.second,
		                                              Color::White, Color::Cyan, Color::Magenta);
	}

	/*this->buttons["GAME_STATE"] = new Button(buttonMiddleCoords.x, buttonMiddleCoords.y, 150, 50,
	                                         &this->font, "New Game",
	                                         Color::White, Color::Cyan, Color::Magenta);*/
}

Vector2i MainMenuState::getButtonMiddleCoors(Vector2u windowSize, int buttonWidth, int buttonHeight,
                                             int paddingBetween, int buttonPosition, int buttonsCount)
{
	Vector2i buttonsFieldDimensions(buttonWidth, buttonHeight * buttonsCount + paddingBetween * (buttonsCount - 1)); //width, height
	return Vector2i(windowSize.x / 2 - buttonWidth / 2,
	                (windowSize.y  - buttonsFieldDimensions.y)/2  - buttonHeight * buttonPosition - paddingBetween * (buttonPosition - 1));
}

MainMenuState::MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states) : State(
	window, supportedKeys)
{
	this->states = states;
	this->initKeybinds();
	this->initFonts();
	this->initButtons();

	this->backgroundTexture = new Texture();
	backgroundTexture->loadFromFile("characters_images/mianScreenBackground.png");

	
	this->background = new Sprite();
	this->background->setTexture(*backgroundTexture);
	this->background->setScale(this->window->getSize().x / 1920.f, this->window->getSize().y / 1080.f);
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

void MainMenuState::endState()
{
	std::cout << "Ending MainMenuState!" << std::endl;
}

void MainMenuState::updateInput(const float& dt)
{
	this->checkForQuit();
}


void MainMenuState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::updateButtons()
{
	/*Updates all the buttons in the state and handles their functionality.*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosView);
		if(it.second->isPressed())
		{
						if (it.first == "4.GAME_STATE")
							this->states->push(new GameState(window, (this->supportedKeys)));
		}	
	}
}

void MainMenuState::renderButtons(RenderTarget* target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void MainMenuState::render(RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(*this->background);
	renderButtons(target);
}
