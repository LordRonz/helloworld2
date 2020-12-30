#pragma once

#include "PlayerDeck.h"

class BaseDeck : public Deck{
private:
    std::stack<Card*> cards;
    Card* dummy{};
    bool pass{};
    unsigned short passDeck{1};
    Card* passedCard{};

public:
    BaseDeck(std::vector<Deck*>* decks);
    ~BaseDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    bool passCard(const unsigned int& trgt, const double& dt);
    Card* getPassedCard();
};
