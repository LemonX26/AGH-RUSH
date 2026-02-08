#pragma once
#include "GameState.h"
#include "Button.h"

class MainMenuState :
	public State
{
private:
	//Variables
	Texture* backgroundTexture;
	Sprite *background;
	Font font;
	std::stack<State*>* states;


	std::map<std::string, Button*> buttons;

	//Functions
	Vector2i getButtonMiddleCoors(Vector2u windowSize, int buttonWidth, int buttonHeight, int paddingBetween,
	                              int buttonPosition, int buttonsCount);
	void initFonts();
	void initKeybinds() override;
	void initButtons();

public:
	MainMenuState(RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	~MainMenuState() override;
	//Functions
	void endState() override;
	void updateInput(const float& dt) override;
	void update(const float& dt) override;
	void updateButtons();
	void renderButtons(RenderTarget* target = nullptr);
	void render(RenderTarget* target = nullptr) override;
};
