#include "Deck.h"

Deck::Deck(unsigned short type) {
    this->type = type;
    if(this->type == Player0) {
	this->pos.x = 10.f;
	this->pos.y = 10.f;
    }
    else if(this->type == Player1) {
	this->pos.x = 600.f;
	this->pos.y = 450.f;
    }
}

Deck::~Deck() {
    for(auto& it: this->cards) {
	delete it.second;
    }
}

void Deck::addCard(Card* card, const std::string kind) {
    this->cards[kind] = card;
    this->cards[kind]->setPosition(this->pos.x, this->pos.y);
}

void Deck::update(const double& dt, const sf::Vector2f mousePos) {
    for(auto& it: this->cards) {
	it.second->update(dt, mousePos);
    }
}

void Deck::render(sf::RenderTarget* target) {
     this->cards["2C"]->render(target);
}

const sf::Vector2f Deck::getPosition() {
    return this->pos;
}
