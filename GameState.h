#pragma once

#include "State.h"

#define PLAYER_COUNT 2

class GameState : public State {
private:
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;
    std::vector<Deck*> decks;
    sf::Texture bgTexture;
    sf::RectangleShape bg;

    void initRenderTexture();
    void initVariables();
    void initBackground();
    void initTextures();
    void initDecks();
    int passDeck{Player1};
    int winner{-1};
    bool begin{};
    void updateDecks(const double& dt);
    bool isComparing{};
    bool passCannotMove{};
    const bool updatePlayer(const double& dt);
    const bool updateComp(const double& dt);
    std::bitset<PLAYER_COUNT> turn;
    std::vector<std::pair<int, Card*>> cmpCards{};
    const bool isValid(const int& selected);
    bool firstMove{true};
    void compareCards();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    ~GameState();
    void updateInput(const double& dt);
    void update(const double& dt);
    void render(sf::RenderTarget* target = nullptr);
};
