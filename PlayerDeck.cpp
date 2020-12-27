#include "PlayerDeck.h"

PlayerDeck::PlayerDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(600.f, 480.f);
}

PlayerDeck::~PlayerDeck() {
    for(auto& it: this->cards) {
	delete it.second;
    }
    this->cards.clear();
}

void PlayerDeck::addCard(Card* card) {
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
    int i = 1;
    for(auto& it: this->cards) {
	it.second->setPosition((1080.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
    //this->cards[tmp]->setPosition(720.f / this->cardCount, this->pos.y);
    std::printf("%d\n", this->cardCount);
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
