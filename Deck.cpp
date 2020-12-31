#include "Deck.h"

Deck::Deck(std::vector<Deck*>* decks) {
    this->decks = decks;
}

Deck::~Deck() {

}

void Deck::addCard(Card* card) {
    ++this->cardCount;
    //this->cards.emplace(card);
    //this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void Deck::update(const double& dt, const sf::Vector2f& mousePos) {
    //for(auto& it: this->cards) {
    //	it.second->update(dt, mousePos);
    //}
}

void Deck::render(sf::RenderTarget* target) {
     //this->cards["2C"]->render(target);
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

const unsigned short& Deck::getCardCount() const {
    return this->cardCount;
}

int Deck::getSelected() {
    return -1;
}

unsigned short Deck::getKindAtIndex(const int& index) {
    return 0;
}
