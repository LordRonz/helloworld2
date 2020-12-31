#pragma once

#include "Deck.h"

class TrashDeck : public Deck {
private:
    std::vector<Card*> cards;
    Card* addedCard{};

public:
    TrashDeck(std::vector<Deck*>* decks);
    ~TrashDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    bool passCard(const unsigned int& trgt, const double& dt);
    bool throwDeck(const double& dt);
    void rearrange();
};
