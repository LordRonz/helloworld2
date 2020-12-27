#include "CompDeck.h"

CompDeck::CompDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(600.f, 10.f);
}

CompDeck::~CompDeck() {
    for(auto& it: this->cards) {
	delete it.second;
    }
    this->cards.clear();
}

void CompDeck::addCard(Card* card) {
    ++this->cardCount;
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

void CompDeck::update(const double& dt, const sf::Vector2f mousePos) {
    for(auto& it: this->cards) {
	it.second->update(dt, mousePos);
    }
}

void CompDeck::render(sf::RenderTarget* target) {
    if(!this->cards.empty())
	this->cards.begin()->second->render(target);
}
