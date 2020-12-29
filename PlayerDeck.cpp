#include "PlayerDeck.h"

PlayerDeck::PlayerDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(500.f, 500.f);
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
    this->rearrange();
    //this->cards[tmp]->setPosition(720.f / this->cardCount, this->pos.y);
    //std::printf("%d\n", this->cardCount);
}

Card* PlayerDeck::getPassedCard() {
    return this->passedCard;
}

const bool PlayerDeck::passCard(unsigned int trgt, const double& dt) {
    if(!this->cards.empty()) {
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
	    this->cards.erase(this->selected);
	    --this->cardCount;
	    this->selected = "";
	    this->rearrange();
	    return true;
	}
    }
    return false;
}

void PlayerDeck::update(const double& dt, const sf::Vector2f mousePos) {
    for(auto& it: this->cards) {
	it.second->update(dt, mousePos);
	if(this->selected == "" && it.second->isClicked()) {
	    std::string tmp = std::to_string(it.second->getVal());
	    switch(it.second->getKind()) {
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
	    this->selected = tmp;
	}
    }
}

void PlayerDeck::reset() {
    this->selected = "";
}

const bool PlayerDeck::canMove(unsigned int kind) {
    for(auto& it: this->cards) {
	if(it.second->getKind() == kind) return true;
    }
    return false;
}

void PlayerDeck::rearrange() {
    int i = 1;
    for(auto& it: this->cards) {
	it.second->setPosition((1160.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
}

void PlayerDeck::render(sf::RenderTarget* target) {
    for(auto& it: this->cards) {
	it.second->render(target);
    }
}

std::string PlayerDeck::getSelected() {
    return this->selected;
}
