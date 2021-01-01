#include "BaseDeck.h"

BaseDeck::BaseDeck(std::vector<Deck*>* decks) : Deck(decks) {
    this->setPosition(10.f, 10.f);
}

BaseDeck::~BaseDeck() {
    while(!this->cards.empty()) {
	delete this->cards.top();
	this->cards.pop();
    }
    delete this->dummy;
}

void BaseDeck::addCard(Card* card) {
    if(!card) return;
    if(!this->cardCount++) {
        this->dummy = card;
        this->dummy->setPosition(this->pos.x, this->pos.y);
        return;
    }
    this->cards.push(card);
    this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void BaseDeck::update(const double& dt, const sf::Vector2f& mousePos) {
    if(!this->cards.empty()) {
	if(this->cards.top())
	   this->cards.top()->update(dt, mousePos);
    } 
}

void BaseDeck::render(sf::RenderTarget* target) {
    if(!target) return;
    if(!this->cards.empty()) {
        if(this->cards.top())
	    this->cards.top()->render(target);
        if(this->dummy)
	   this->dummy->render(target);
    }
}

Card* BaseDeck::getPassedCard() {
    return this->passedCard;
}

bool BaseDeck::passCard(const unsigned int& trgt, const double& dt) {
    if(!this->cards.empty() && this->cards.top()) {
	this->passedCard = this->cards.top();
	if(vectorDistance(this->cards.top()->getPosition(), (*this->decks)[trgt]->getPosition()) > 20.f) {
	    this->cards.top()->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    if(trgt == Player1 || trgt == Trash) this->cards.top()->flip();
	    (*this->decks)[trgt]->addCard(this->cards.top());
	    this->cards.pop();
	    --this->cardCount;
	    return true;
	}
    }
    return false;
}
