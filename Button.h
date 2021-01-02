#pragma once

#include "BaseDeck.h"

enum btn_states{BTN_IDLE = 0, BTN_HOVER, BTN_ACTIVE};

class Button {
private:
    unsigned short btnState;
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;
    sf::Color textIdleColor;
    sf::Color textHoverColor;
    sf::Color textActiveColor;
    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
    sf::Color outlineIdleColor;
    sf::Color outlineHoverColor;
    sf::Color outlineActiveColor;

public:
    Button(float x, float y, float width, float height,
	    sf::Font* font, std::string text, unsigned charSize,
	    sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
	    sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor,
	    sf::Color outlineIdleColor = sf::Color::Transparent, sf::Color outlineHoverColor = sf::Color::Transparent, sf::Color outlineActiveColor = sf::Color::Transparent);
    ~Button();

    const bool isPressed();
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    void setText(const std::string& text);
};
