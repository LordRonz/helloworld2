#pragma once

#include "TrashDeck.h"

class CompDeck : public Deck {
private:
    std::map<std::string, Card*> cards;
    std::string selected;

public:
    CompDeck(std::vector<Deck*>* decks);
    virtual ~CompDeck();
    void addCard(Card* card);
    void passCard(unsigned int trgt, const double& dt);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    std::string getSelected();
};
