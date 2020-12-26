#include "BaseDeck.h"

BaseDeck::BaseDeck(std::vector<Deck*>* decks) : Deck(decks) {
    this->setPosition(10.f, 10.f);
}

BaseDeck::~BaseDeck() {
    while(!this->cards.empty()) {
	delete this->cards.top();
	this->cards.pop();
    }
}

void BaseDeck::addCard(Card* card) {
    this->cards.emplace(card);
    this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void BaseDeck::update(const double& dt, const sf::Vector2f mousePos) {
    if(!this->cards.empty()) {
    	this->cards.top()->update(dt, mousePos);
    }    
    this->passCard();
}

void BaseDeck::render(sf::RenderTarget* target) {
    if(!this->cards.empty())
	this->cards.top()->render(target);
}

void BaseDeck::passCard() {
    if(!this->cards.empty()) {
	(*this->decks)[1]->addCard(this->cards.top());
	this->cards.pop();
    } 
}
