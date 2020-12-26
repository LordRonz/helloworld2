#pragma once

#include "Card.h"

enum deck_type {Player0, Player1, Player2};

class Deck {
protected:
    sf::Vector2f pos;
    unsigned short type;
    std::vector<Deck*>* decks;
    
public:
    Deck(std::vector<Deck*>* decks);
    virtual ~Deck();
    virtual void update(const double& dt, const sf::Vector2f mousePos);
    virtual void render(sf::RenderTarget* target);
    virtual void addCard(Card* card);
    const sf::Vector2f getPosition();
    virtual void setPosition(const float x, const float y);
};
