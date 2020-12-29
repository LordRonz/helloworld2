#pragma once

#include "TrashDeck.h"

class CompDeck : public Deck {
private:
    std::map<std::string, Card*> cards;
    std::string selected;
    Card* passedCard;

public:
    CompDeck(std::vector<Deck*>* decks);
    virtual ~CompDeck();
    void addCard(Card* card);
    const bool passCard(unsigned int trgt, const double& dt);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    Card* getPassedCard();
    std::string getSelected();
};
