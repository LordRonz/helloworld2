#pragma once

#include "GameState.h"

class MainMenuState : public State {
private:
    sf::Texture bgTexture;
    sf::RectangleShape bg;
    sf::Font font;

    sf::RectangleShape btnBackground;
    std::unordered_map<std::string, Button*> buttons;
    void initGui();
    void initFonts();

public:
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    ~MainMenuState();
    void updateInput(const double& dt);
    void updateButtons();
    void update(const double& dt);
    void renderButtons(sf::RenderTarget* target);
    void render(sf::RenderTarget* target = NULL);
};
