#pragma once

#include "State.h"

class StatePlaying : public State {
private:
    Card* player;
    void initTextures();

public:
    StatePlaying(sf::RenderWindow* window, std::stack<State*>* states);
    ~StatePlaying();
    void endState();
    void updateInput(const double& dt);
    void update(const double& dt);
    void render(sf::RenderTarget* target = NULL);
};
