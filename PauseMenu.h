#pragma once

#include "Button.h"

class PauseMenu {
private:
    sf::Font* font;
    sf::Text text;

    sf::RectangleShape bg;
    sf::RectangleShape container;

    std::unordered_map<std::string, Button*> buttons;

public:
    PauseMenu(sf::Window* window, sf::Font* font);
    ~PauseMenu();

    bool isButtonPressed(const std::string& key);
    void addButton(
	const std::string& key,
	const float& y,
	const float& width,
	const float& height,
	const unsigned& char_sz,
	const std::string& text);
    void update(const sf::Vector2f& mousePosWindow);
    void render(sf::RenderTarget* target);
};
