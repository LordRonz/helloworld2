#pragma once

#include "Deck.h"

class BaseDeck : public Deck{
private:

public:
    BaseDeck();
    virtual ~BaseDeck();
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
};
