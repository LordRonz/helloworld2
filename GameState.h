#pragma once

#include "State.h"

class GameState : public State {
private:
    std::vector<Deck*> decks;
    sf::Texture bgTexture;
    sf::RectangleShape bg;
    void initVariables();
    void initBackground();
    void initTextures();
    void initDecks();
    int passDeck{Player1};
    bool begin{};
    void updateDecks(const double& dt);
    bool isPassing{};
    bool passCannotMove{};
    const bool updatePlayer(const double& dt);
    const bool updateComp(const double& dt);
    std::vector<bool> turn;
    std::vector<std::pair<int, Card*>> cmpCards{};
    const bool isValid(const int& selected);
    const bool firstMove{true};
    void compareCards();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    ~GameState();
    void endState();
    void updateInput(const double& dt);
    void update(const double& dt);
    void render(sf::RenderTarget* target = NULL);
};
