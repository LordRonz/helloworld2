#include "PlayerDeck.h"

PlayerDeck::PlayerDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(500.f, 500.f);
    this->selected = -1;
}

PlayerDeck::~PlayerDeck() {
    for(auto& it: this->cards) {
	delete it;
    }
    this->cards.clear();
}

void PlayerDeck::addCard(Card* card) {
    ++this->cardCount;
    this->cards.push_back(card);
    this->rearrange();
    //this->cards[tmp]->setPosition(720.f / this->cardCount, this->pos.y);
    //std::printf("%d\n", this->cardCount);
}

Card* PlayerDeck::getPassedCard() {
    return this->passedCard;
}

unsigned short PlayerDeck::getKindAtIndex(int index) {
    return index >= 0 && index < this->cards.size() ? this->cards[index]->getKind() : -1;
}

const bool PlayerDeck::passCard(unsigned int trgt, const double& dt) {
    if(!this->cards.empty() && this->selected >= 0 && this->selected < this->cards.size()) {
	this->passedCard = this->cards[this->selected];
	float dist = std::sqrt(
	    std::pow((this->cards[this->selected]->getPosition().x - (*this->decks)[trgt]->getPosition().x), 2) +
	    std::pow((this->cards[this->selected]->getPosition().y - (*this->decks)[trgt]->getPosition().y), 2));
	//std::printf("%f\n", dist);
	//system("cls");
	//std::printf("%f\n", (*this->decks)[this->passDeck]->getPosition().x);
	if(dist > 20.f) {
	    this->cards[this->selected]->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    (*this->decks)[trgt]->addCard(this->cards[this->selected]);
	    this->cards.erase(this->cards.begin() + this->selected);
	    --this->cardCount;
	    this->selected = -1;
	    this->rearrange();
	    return true;
	}
    }
    return false;
}

void PlayerDeck::update(const double& dt, const sf::Vector2f mousePos) {
    for(int i = 0, j = this->cards.size(); i < j; ++i) {
	this->cards[i]->update(dt, mousePos);
	if(this->selected == -1 && this->cards[i]->isClicked()) {
	    this->selected = i;
	}
    }
}

void PlayerDeck::reset() {
    this->selected = -1;
}

const bool PlayerDeck::canMove(unsigned int kind) {
    for(auto& it: this->cards) {
	if(it->getKind() == kind) return true;
    }
    return false;
}

void PlayerDeck::rearrange() {
    int i = 1;
    for(auto& it: this->cards) {
	it->setPosition((1160.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
}

void PlayerDeck::render(sf::RenderTarget* target) {
    for(auto& it: this->cards) {
	it->render(target);
    }
}

const int PlayerDeck::getSelected() {
    return this->selected;
}
