#pragma once

#include "CompDeck.h"

class PlayerDeck : public Deck{
private:
    std::vector<Card*> cards;
    int selected;
    Card* passedCard{};

public:
    PlayerDeck(std::vector<Deck*>* decks);
    virtual ~PlayerDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    bool passCard(const unsigned int& trgt, const double& dt);
    void rearrange();
    void reset();
    Card* getPassedCard();
    int getSelected();
    bool canMove(const unsigned int& kind);
    unsigned short getKindAtIndex(const int& index);
};
