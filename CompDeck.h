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
    bool passCard(const unsigned int& trgt, const double& dt);
    void update(const double& dt, const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    Card* getPassedCard();
    bool canMove(const unsigned int& kind);
    void artificialStupidity(Card* card);
    void reset();
    int getSelected();
};
