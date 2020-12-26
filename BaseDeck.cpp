#include "BaseDeck.h"

BaseDeck::BaseDeck() {
    this->pos.x = 10.f;
    this->pos.x = 10.f;
}

BaseDeck::~BaseDeck() {
    while(!this->cards.empty()) {
	delete this->cards.top();
	this->cards.pop();
    }
}

void BaseDeck::update(const double& dt, const sf::Vector2f mousePos) {
    if(!this->cards.empty()) {
    	this->cards.top()->update(dt, mousePos);
    }
}

void BaseDeck::render(sf::RenderTarget* target) {
     this->cards.top()->render(target);
}
