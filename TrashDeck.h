#pragma once

#include "Deck.h"

class TrashDeck : public Deck {
private:
    std::vector<Card*> cards;

public:
    TrashDeck(std::vector<Deck*>* decks, const float& x, const float& y, sf::Font* font);
    ~TrashDeck();
    void addCard(Card* card);
    void render(sf::RenderTarget* target);
    bool passCard(const unsigned int& trgt, const double& dt);
    bool throwDeck(const double& dt);
    void rearrange();
};
