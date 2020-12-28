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

void CompDeck::passCard(unsigned int trgt, const double& dt) {
    if(!this->cards.empty()) {
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
	    if(trgt == Trash || trgt == Player1) this->cards[this->selected]->flip();
	    (*this->decks)[trgt]->addCard(this->cards[this->selected]);
	    this->cards.erase(this->selected);
	    --this->cardCount;
	}
    } 
}

std::string CompDeck::getSelected() {
    return this->selected;
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
