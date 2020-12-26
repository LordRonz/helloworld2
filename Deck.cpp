#include "Deck.h"

Deck::Deck() {
}

Deck::~Deck() {
    while(!this->cards.empty()) {
	delete this->cards.top();
	this->cards.pop();
    }
}

void Deck::addCard(Card* card) {
    this->cards.emplace(card);
    this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void Deck::update(const double& dt, const sf::Vector2f mousePos) {
    //for(auto& it: this->cards) {
    //	it.second->update(dt, mousePos);
    //}
}

void Deck::render(sf::RenderTarget* target) {
     //this->cards["2C"]->render(target);
}

const sf::Vector2f Deck::getPosition() {
    return this->pos;
}
