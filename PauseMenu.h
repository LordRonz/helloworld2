#pragma once

#include "GameState.h"

class PauseMenu {
private:
    sf::Font* font;
    sf::Text text;

    sf::RectangleShape bg;

    std::unordered_map<std::string, Button*> buttons;

public:

};
