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

void Deck::update(const double& dt, const sf::Vector2f mousePos) {
    //for(auto& it: this->cards) {
    //	it.second->update(dt, mousePos);
    //}
}

void Deck::render(sf::RenderTarget* target) {
     //this->cards["2C"]->render(target);
}

void Deck::reset() {}

const bool Deck::canMove(unsigned int kind) {
    return false;
}

Card* Deck::getPassedCard() {
    return nullptr;
}

const bool Deck::passCard(unsigned int trgt, const double& dt) {
    return 1 > 2;
}

const sf::Vector2f Deck::getPosition() {
    return this->pos;
}

void Deck::artificialStupidity(Card* card) {
    
}

void Deck::setPosition(const float x, const float y) {
    this->pos.x = x;
    this->pos.y = y;
}

int Deck::getCardCount() {
    return this->cardCount;
}

std::string Deck::getSelected() {
    return "";
}
