#include "CompDeck.h"

CompDeck::CompDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(600.f, 10.f);
    this->selected = -1;
}

CompDeck::~CompDeck() {
    for(auto& it: this->cards) {
	delete it;
    }
}

void CompDeck::addCard(Card* card) {
    if(card) {
	++this->cardCount;
	this->cards.push_back(card);
	this->cards.back()->setPosition(this->pos.x, this->pos.y);
    }
}

Card* CompDeck::getPassedCard() {
    return this->passedCard;
}

void CompDeck::artificialStupidity(Card* card) {
    if(card) {
	int mxIndex = 0;
	int mx = 0;
	for(int i = 0, j = this->cards.size(); i < j; ++i) {
	    if(!this->cards[i]) continue;
	    if(this->cards[i]->getKind() == card->getKind()) {
		int tmp;
		if((tmp = this->cards[i]->getVal()) > mx) {
		    mx = tmp;
		    mxIndex = i;
		}
	    }
	}
	this->selected = mxIndex;
    }
}

bool CompDeck::passCard(const unsigned int& trgt, const double& dt) {
    if(!this->cards.empty() && this->selected < this->cards.size() && this->cards[this->selected]) {
	this->passedCard = this->cards[this->selected];
	if(vectorDistance(this->cards[this->selected]->getPosition(), (*this->decks)[trgt]->getPosition()) > 20.f) {
	    this->cards[this->selected]->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    if(trgt == Trash || trgt == Player1) this->cards[this->selected]->flip();
	    (*this->decks)[trgt]->addCard(this->cards[this->selected]);
	    this->cards.erase(this->cards.begin() + this->selected);
	    --this->cardCount;
	    this->selected = -1;
	    return true;
	}
    }
    return false;
}

int CompDeck::getSelected() {
    return this->selected;
}

bool CompDeck::canMove(const unsigned int& kind) {
    for(auto& it: this->cards) {
	if(it && it->getKind() == kind) return true;
    }
    return false;
}

void CompDeck::reset() {
    this->selected = -1;
}

void CompDeck::update(const double& dt, const sf::Vector2f& mousePos) {
    for(auto& it: this->cards) {
	if(it)
	    it->update(dt, mousePos);
    }
}

void CompDeck::render(sf::RenderTarget* target) {
    if(target) {
	if(!this->cards.empty() && this->cards.front())
	    this->cards.front()->render(target);
	if(this->selected != -1 && this->cards[this->selected]) {
	    this->cards[this->selected]->render(target);
	}
    }
}
