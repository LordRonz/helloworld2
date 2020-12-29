#include "TrashDeck.h"

TrashDeck::TrashDeck(std::vector<Deck*>* decks) : Deck(decks)  {
    this->setPosition(500.f, 240.f);
}

TrashDeck::~TrashDeck() {
    for(auto& it: cards) {
	delete it;
    }
}

void TrashDeck::addCard(Card* card) {
    ++this->cardCount;
    if(card) {
	this->cards.push_back(card);
    }
    int i = 1;
    for(auto& it: this->cards) {
	it->setPosition((1160.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
}

void TrashDeck::update(const double& dt, const sf::Vector2f mousePos) {

}

void TrashDeck::render(sf::RenderTarget* target) {
    for(auto& it: this->cards) {
	it->render(target);
    }
}
