#include "CompDeck.h"

CompDeck::CompDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(600.f, 10.f);
    this->selected = -1;
    this->initRandomEngine();
}

CompDeck::~CompDeck() {
    for(auto& it: this->cards)
	delete it;
}

void CompDeck::initRandomEngine() {
    this->rng.seed(std::random_device{}());
}

void CompDeck::addCard(Card* card) {
    if(!card) return;
    ++this->cardCount;
    this->cards.push_back(card);
    this->cards.back()->setPosition(this->pos.x, this->pos.y);
}

Card* CompDeck::getPassedCard() {
    return this->passedCard;
}

void CompDeck::artificialStupidity(Card* card) {
    if(this->cards.empty()) return;
    if(!card) {
	std::uniform_int_distribution<> res(0, this->cards.size() - 1);
	this->selected = res(this->rng);
	return;
    }
    unsigned mnIndexFound(0), mnFound(15), mnIndexNotFound(0), mnNotFound(15);
    bool found{};
    for(unsigned i = 0, j = this->cards.size(); i < j; ++i) {
	if(!this->cards[i]) continue;
	if(this->cards[i]->getKind() == card->getKind()) {
	    unsigned tmp(0);
	    if((tmp = this->cards[i]->getVal()) > card->getVal()) {
	        if(tmp < mnFound) {
		    mnFound = tmp;
		    mnIndexFound = i;
		    found = true;
		}
	    }
	    else {
		if(tmp < mnNotFound) {
		    mnNotFound = tmp;
		    mnIndexNotFound = i;
		}
	    }
        }
    }
    this->selected = found ? mnIndexFound : mnIndexNotFound;
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
    this->passedCard = nullptr;
}

void CompDeck::update(const double& dt, const sf::Vector2f& mousePos) {

}

void CompDeck::render(sf::RenderTarget* target) {
    if(!target || this->cards.empty()) return;
    unsigned i = 0;
    for(; this->selected == i && i < this->cards.size() - 1; ++i);
    if(this->cards[i])
        this->cards[i]->render(target);
    if(this->selected != -1 && this->cards[this->selected])
        this->cards[this->selected]->render(target);
}
