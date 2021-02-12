#pragma once

#include "Card.h"

enum Decks {Player0, Player1, Player2, Trash};

class Deck {
protected:
    std::vector<Deck*>* decks;
    sf::Vector2f pos;
    sf::Text text;
    sf::Font* font;
    unsigned short type;
    unsigned short cardCount{};
    virtual void initText(sf::Font* font, unsigned sz);
    
public:
    Deck(std::vector<Deck*>* decks, const float& x, const float& y, sf::Font* font);
    virtual ~Deck();
    virtual void update(const double& dt, const sf::Vector2f& mousePos);
    virtual void render(sf::RenderTarget* target);
    virtual void addCard(Card* card) = 0;
    const sf::Vector2f& getPosition() const;
    virtual void setPosition(const float& x, const float& y);
    virtual void setPosition(const sf::Vector2f& pos);
    virtual bool passCard(const unsigned int& trgt, const double& dt) = 0;
    virtual Card* getPassedCard();
    virtual void reset();
    virtual bool canMove(const unsigned int& kind);
    virtual int getSelected();
    virtual void artificialStupidity(Card* card);
    const unsigned short& getCardCount() const;
    virtual unsigned short getKindAtIndex(const int& index);
};
