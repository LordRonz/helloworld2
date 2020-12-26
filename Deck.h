#pragma once

#include "Card.h"

enum deck_type {Player0, Player1, Player2};

class Deck {
private:
    std::map<std::string, Card*> cards;
    sf::Vector2f pos;
    unsigned short type;
    
public:
    Deck(unsigned short type);
    virtual ~Deck();
    virtual void update(const double& dt, const sf::Vector2f mousePos);
    virtual void render(sf::RenderTarget* target);
    virtual void addCard(Card* card, const std::string kind);
    const sf::Vector2f getPosition();
};
