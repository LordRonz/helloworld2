#include "Deck.h"

Deck::Deck() {
    
}

Deck::~Deck() {
    for(auto& it: cards) {
	delete it.second;
    }
}

void Deck::addCard(Card* card, std::string kind) {
    cards[kind] = card;
}

void Deck::update(const double& dt, const sf::Vector2f mousePos) {
    for(auto& it: cards) {
	it.second->update(dt, mousePos);
    }
}

void Deck::render(sf::RenderTarget* target) {
     this->cards["2C"]->render(target);
}
