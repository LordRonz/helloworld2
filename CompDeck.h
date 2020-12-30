#pragma once

#include "TrashDeck.h"

class CompDeck : public Deck {
private:
    std::vector<Card*> cards;
    int selected;
    Card* passedCard;

public:
    CompDeck(std::vector<Deck*>* decks);
    virtual ~CompDeck();
    void addCard(Card* card);
    const bool passCard(unsigned int trgt, const double& dt);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    Card* getPassedCard();
    const bool canMove(unsigned int kind);
    void artificialStupidity(Card* card);
    void reset();
    const int getSelected();
};
