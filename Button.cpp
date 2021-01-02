#include "Button.h"

Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,  unsigned charSize,
	sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color outlineIdleColor, sf::Color outlineHoverColor, sf::Color outlineActiveColor) : btnState(BTN_IDLE) {
    
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idleColor);
    this->shape.setOutlineThickness(1.f);
    this->shape.setOutlineColor(outlineIdleColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::Green);
    this->text.setCharacterSize(charSize);
    this->text.setPosition(
	this->shape.getPosition().x + (this->shape.getGlobalBounds().width / 2.f) - this->text.getGlobalBounds().width / 2.f,
	this->shape.getPosition().y + (this->shape.getGlobalBounds().height / 2.f) - this->text.getGlobalBounds().height / 2.f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->textIdleColor = textIdleColor;
    this->textHoverColor = textHoverColor;
    this->textActiveColor = textActiveColor;

    this->outlineIdleColor = outlineIdleColor;
    this->outlineHoverColor = outlineHoverColor;
    this->outlineActiveColor = outlineActiveColor;

}

Button::~Button() {}

const bool Button::isPressed() {
    return this->btnState == BTN_ACTIVE;
}

void Button::update(const sf::Vector2f& mousePos) {
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
	    this->text.setFillColor(this->textIdleColor);
	    this->shape.setOutlineColor(this->outlineIdleColor);
	    break;
	case BTN_HOVER:
	    this->shape.setFillColor(this->hoverColor);
	    this->text.setFillColor(this->textHoverColor);
	    this->shape.setOutlineColor(this->outlineHoverColor);
	    break;
	case BTN_ACTIVE:
	    this->shape.setFillColor(this->activeColor);
	    this->text.setFillColor(this->textActiveColor);
	    this->shape.setOutlineColor(this->outlineActiveColor);
	    break;
	default:
	    this->shape.setFillColor(sf::Color::Red);
	    this->text.setFillColor(sf::Color::Blue);
	    this->shape.setOutlineColor(sf::Color::Green);
	    break;
    }
}

void Button::setText(const std::string& text) {
    this->text.setString(text);
}

void Button::render(sf::RenderTarget* target) {
    target->draw(this->shape);
    target->draw(this->text);
}
