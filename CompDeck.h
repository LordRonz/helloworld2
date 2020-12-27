#pragma once

#include "Deck.h"

class CompDeck : public Deck {
private:
    std::map<std::string, Card*> cards;
public:
    CompDeck(std::vector<Deck*>* decks);
    virtual ~CompDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};
