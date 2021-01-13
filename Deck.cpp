#include "Deck.h"

Deck::Deck(std::vector<Deck*>* decks, const float& x, const float& y) : decks(decks), pos(sf::Vector2f(x, y)) {
}

Deck::~Deck() {

}

void Deck::addCard(Card* card) {
    ++this->cardCount;
    //this->cards.emplace(card);
    //this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void Deck::update(const double& dt, const sf::Vector2f& mousePos) {
 
}

void Deck::render(sf::RenderTarget* target) {

}

void Deck::reset() {}

bool Deck::canMove(const unsigned int& kind) {
    return false;
}

Card* Deck::getPassedCard() {
    return nullptr;
}

bool Deck::passCard(const unsigned int& trgt, const double& dt) {
    return false;
}

const sf::Vector2f& Deck::getPosition() const {
    return this->pos;
}

void Deck::artificialStupidity(Card* card) {
    
}

void Deck::setPosition(const float& x, const float& y) {
    this->pos.x = x;
    this->pos.y = y;
}

void Deck::setPosition(const sf::Vector2f& pos) {
    this->pos = pos;
}

const unsigned short& Deck::getCardCount() const {
    return this->cardCount;
}

int Deck::getSelected() {
    return -1;
}

unsigned short Deck::getKindAtIndex(const int& index) {
    return 0;
}
