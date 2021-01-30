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
    sf::Font font;
    PauseMenu* pMenu;
    EndGame* endGame;
    bool firstMove{true};
    bool someoneWon{};
    std::bitset<PLAYER_COUNT> turn;
    std::vector<std::pair<int, Card*>> cmpCards{};
    int passDeck{Player1};
    int winner{-1};
    bool begin{};

    // Functions
    void initRenderTexture();
    void initBackground();
    void initTextures();
    void initDecks();
    void initFonts();
    void initPause();
    void initEndGame();
    void updateDecks(const double& dt);
    void updateEndGame(const double& dt);
    bool updatePlayer(const double& dt);
    bool updateComp(const double& dt);
    const bool isValid(const int& selected) const;
    void compareCards();

public:
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    ~GameState();
    void updateInput(const double& dt);
    void update(const double& dt);
    void render(sf::RenderTarget* target = nullptr);
};
