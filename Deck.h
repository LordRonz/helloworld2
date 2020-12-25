#pragma once

#include "Card.h"

class Deck {
private:
    std::map<std::string, Card*> cards;
    
public:
    Deck();
    virtual ~Deck();
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    void addCard(Card* card, std::string kind);
};
