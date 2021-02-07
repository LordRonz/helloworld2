#pragma once

#include "PauseMenu.h"

class EndGame {
private:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;
    std::unordered_map<std::string, Button*> buttons;
    void initButtons();
    void initBackground();

public:
    EndGame(sf::Font* font);
    ~EndGame();
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    void setText(const std::string& text);
    void addButton(
	const std::string& key,
	const float& y,
	const float& width,
	const float& height,
	const unsigned& char_sz,
	const std::string& text);
};
