#include "Button.h"

Button::Button(float x, float y, float width, float height, sf::Font* font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) : btnState(BTN_IDLE) {
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Green);
    this->text.setCharacterSize(12);
    this->text.setPosition(
	this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
	this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;
    this->shape.setFillColor(idleColor);
}

Button::~Button() {}

const bool Button::isPressed() {
    return this->btnState == BTN_ACTIVE;
}

void Button::update(const sf::Vector2f mousePos) {
    this->btnState = BTN_IDLE;

    if(this->shape.getGlobalBounds().contains(mousePos)) {
	this->btnState = BTN_HOVER;

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
	    this->btnState = BTN_ACTIVE;
	}
    }
    switch(this->btnState) {
	case BTN_IDLE:
	    this->shape.setFillColor(this->idleColor);
	    break;
	case BTN_HOVER:
	    this->shape.setFillColor(this->hoverColor);
	    break;
	case BTN_ACTIVE:
	    this->shape.setFillColor(this->activeColor);
	    break;
	default:
	    this->shape.setFillColor(sf::Color::Magenta);
	    break;
    }
}

void Button::render(sf::RenderTarget* target) {
    target->draw(this->shape);
    target->draw(this->text);
}
