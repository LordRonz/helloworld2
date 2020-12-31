#pragma once

#include "Card.h"

enum deck_type {Player0, Player1, Player2, Trash};

class Deck {
protected:
    sf::Vector2f pos;
    unsigned short type;
    std::vector<Deck*>* decks;
    unsigned short cardCount{};
    
public:
    Deck(std::vector<Deck*>* decks);
    virtual ~Deck();
    virtual void update(const double& dt, const sf::Vector2f& mousePos);
    virtual void render(sf::RenderTarget* target);
    virtual void addCard(Card* card);
    const sf::Vector2f& getPosition() const;
    virtual void setPosition(const float& x, const float& y);
    virtual bool passCard(const unsigned int& trgt, const double& dt);
    virtual Card* getPassedCard();
    virtual void reset();
    virtual bool canMove(const unsigned int& kind);
    virtual int getSelected();
    virtual void artificialStupidity(Card* card);
    const unsigned short& getCardCount() const;
    virtual unsigned short getKindAtIndex(const int& index);
};
