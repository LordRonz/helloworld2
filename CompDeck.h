#pragma once

#include "TrashDeck.h"

class CompDeck : public Deck {
private:
    std::vector<Card*> cards;
    int selected;
    Card* passedCard;
    std::default_random_engine rng;
    void initRandomEngine();

public:
    CompDeck(std::vector<Deck*>* decks, const float& x, const float& y);
    ~CompDeck();
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
