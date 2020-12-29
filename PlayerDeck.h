#pragma once

#include "CompDeck.h"

class PlayerDeck : public Deck{
private:
    std::map<std::string, Card*> cards;
    std::string selected;
    Card* passedCard{};

public:
    PlayerDeck(std::vector<Deck*>* decks);
    virtual ~PlayerDeck();
    void addCard(Card* card);
    void update(const double& dt, const sf::Vector2f mousePos);
    void render(sf::RenderTarget* target);
    const bool passCard(unsigned int trgt, const double& dt);
    void rearrange();
    void reset();
    Card* getPassedCard();
    std::string getSelected();
};
