#pragma once

#include "Deck.h"

class PlayerDeck : public Deck{
private:
    std::map<std::string, Card*> cards;
public:
    PlayerDeck(std::vector<Deck*>* decks);
    virtual ~PlayerDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};
