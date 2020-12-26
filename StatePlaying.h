#pragma once

#include "State.h"

class StatePlaying : public State {
private:
    std::vector<Deck*> decks;
    void initTextures();
    void initDecks();

public:
    StatePlaying(sf::RenderWindow* window, std::stack<State*>* states);
    ~StatePlaying();
    void endState();
    void updateInput(const double& dt);
    void update(const double& dt);
    void render(sf::RenderTarget* target = NULL);
};
