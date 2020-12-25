#pragma once

#include "Card.h"

class Deck {
private:
    std::map<std::string, Card>* cards;
    void initCards();

public:
    Deck();
    virtual ~Deck();
    void update();
    void render();
};
