#pragma once

#include "PauseMenu.h"

class EndGame {
private:
    sf::RectangleShape shape;
    sf::Font* font;
    sf::Text text;
    std::vector<Button*> buttons;
    void initButtons();
    void initBackground();

public:
    EndGame(sf::Font* font);
    ~EndGame();
    void update(const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    void setText(const std::string& text);
};
