#pragma once

#include "PlayerDeck.h"

class BaseDeck : public Deck{
private:
    std::stack<Card*> cards;
    bool pass{};
public:
    BaseDeck(std::vector<Deck*>* decks);
    virtual ~BaseDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    void passCard();
};