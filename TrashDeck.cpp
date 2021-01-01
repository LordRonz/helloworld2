#include "TrashDeck.h"

TrashDeck::TrashDeck(std::vector<Deck*>* decks) : Deck(decks)  {
    this->setPosition(500.f, 240.f);
}

TrashDeck::~TrashDeck() {
    for(auto& it: this->cards) {
	delete it;
    }
}

void TrashDeck::addCard(Card* card) {
    if(!card) return;
    this->addedCard = card;
    ++this->cardCount;
    this->cards.push_back(card);
    this->rearrange();
}

bool TrashDeck::passCard(const unsigned int& trgt, const double& dt) {
    return this->throwDeck(dt);
}

bool TrashDeck::throwDeck(const double& dt) {
    if(this->cards.empty()) return false;
    for(auto& it: this->cards) {
	if(!it) continue;
	if(vectorDistance(it->getPosition(), sf::Vector2f(1290.f, 360.f)) > 20.f) {
	    it->move(dt, 1290.f, 360.f);
	}
	else {
	    delete it;
	    it = nullptr;
	    --this->cardCount;
	    //std::printf("%d\n", this->cardCount);
	}
    }
    if(!this->cardCount) {
	//std::puts("Cleared");
	this->cards.clear();
    }
    return !this->cardCount;
}

void TrashDeck::rearrange() {
    int i = 1;
    for(auto& it: this->cards) {
	if(it)
	    it->setPosition((1160.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
}

void TrashDeck::update(const double& dt, const sf::Vector2f& mousePos) {

}

void TrashDeck::render(sf::RenderTarget* target) {
    if(!target) return;
    for(auto& it: this->cards) {
        if(it)
	   it->render(target);
    }
}
