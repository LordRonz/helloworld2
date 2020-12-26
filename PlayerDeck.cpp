#include "PlayerDeck.h"

PlayerDeck::PlayerDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(600.f, 500.f);
}

PlayerDeck::~PlayerDeck() {
    for(auto& it: this->cards) {
	delete it.second;
    }
    this->cards.clear();
}

void PlayerDeck::addCard(Card* card) {
    std::string tmp = std::to_string(card->getVal());
    switch(card->getKind()) {
	case Diamonds:
	    tmp += 'D';
	    break;
	case Hearts:
	    tmp += 'H';
	    break;
	case Clubs:
	    tmp += 'C';
	    break;
	case Spades:
	    tmp += 'S';
	    break;
    }
    this->cards[tmp] = card;
    this->cards[tmp]->setPosition(this->pos.x, this->pos.y);
}

void PlayerDeck::update(const double& dt, const sf::Vector2f mousePos) {
    for(auto& it: this->cards) {
	it.second->update(dt, mousePos);
    }
}

void PlayerDeck::render(sf::RenderTarget* target) {
    for(auto& it: this->cards) {
	it.second->render(target);
    }
}
