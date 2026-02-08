#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor,
               sf::Color hoverColor, sf::Color activeColor)
{
	this->buttonState = BTN_IDLE;
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setSize(sf::Vector2f(width, height));
	if (font == nullptr)
	{
		font = new sf::Font();
		font->loadFromFile("Fonts/Comfortaa-VariableFont_wght.ttf");
	}
	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(20);

	this->text.setPosition(
		this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width /
		2.f,
		this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height
		/ 2.f
	);

	this->idleColor = idleColor;
	this->hoverColor = hoverColor;
	this->activeColor = activeColor;
	this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
	target->draw(this->text);
}

void Button::update(const sf::Vector2f mousePos)
{
	//Idle
	this->shape.setFillColor(this->idleColor);
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;
		this->shape.setFillColor(this->hoverColor);
		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
			this->shape.setFillColor(this->activeColor);
		}
	}
}

const bool Button::isPressed() const
{
	return this->buttonState == BTN_ACTIVE;
}
