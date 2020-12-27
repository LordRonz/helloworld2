#pragma once

#include "State.h"

class GameState : public State {
private:
    std::vector<Deck*> decks;
    void initTextures();
    void initDecks();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    ~GameState();
    void endState();
    void updateInput(const double& dt);
    void update(const double& dt);
    void render(sf::RenderTarget* target = NULL);
};
