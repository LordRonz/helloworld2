#pragma once

#include "Deck.h"

class TrashDeck : public Deck {
private:
    std::vector<Card*> cards;

public:
    TrashDeck(std::vector<Deck*>* decks);
    virtual ~TrashDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};
