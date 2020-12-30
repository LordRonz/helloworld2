#include "CompDeck.h"

CompDeck::CompDeck(std::vector<Deck*>* decks) :Deck(decks) {
    this->setPosition(600.f, 10.f);
    this->selected = "";
}

CompDeck::~CompDeck() {
    for(auto& it: this->cards) {
	delete it.second;
    }
    this->cards.clear();
}

void CompDeck::addCard(Card* card) {
    ++this->cardCount;
    std::map<unsigned short, std::string> val {
	{1, "2"},
	{2, "3"},
	{3, "4"},
	{4, "5"},
	{5, "6"},
	{6, "7"},
	{7, "8"},
	{8, "9"},
	{9, "10"},
	{10, "J"},
	{11, "Q"},
	{12, "K"},
	{13, "A"}
    };
    std::string tmp = val[card->getVal()];
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

Card* CompDeck::getPassedCard() {
    return this->passedCard;
}

void CompDeck::artificialStupidity(Card* card) {
    std::string tmp;
    switch(card->getKind()) {
	case Diamonds:
	    tmp = "D";
	    break;
	case Hearts:
	    tmp = "H";
	    break;
	case Clubs:
	    tmp = "C";
	    break;
	case Spades:
	    tmp = "S";
	    break;
    }
    std::vector<std::string> val {"A", "K", "Q", "J", "10", "9", "8", "7", "6", "5", "4", "3", "2"};
    for(auto& it: val) {
	if(this->cards.find(it + tmp) != this->cards.end()) {
	    this->selected = it + tmp;
	    break;
	}
    }
}

const bool CompDeck::passCard(unsigned int trgt, const double& dt) {
    if(!this->cards.empty() && this->cards.find(this->selected) != this->cards.end()) {
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
	    if(trgt == Trash || trgt == Player1) this->cards[this->selected]->flip();
	    (*this->decks)[trgt]->addCard(this->cards[this->selected]);
	    this->cards.erase(this->selected);
	    --this->cardCount;
	    this->selected = "";
	    return true;
	}
    }
    return false;
}

std::string CompDeck::getSelected() {
    return this->selected;
}

const bool CompDeck::canMove(unsigned int kind) {
    for(auto& it: this->cards) {
	if(it.second->getKind() == kind) return true;
    }
    return false;
}

void CompDeck::reset() {
    this->selected = "";
}

void CompDeck::update(const double& dt, const sf::Vector2f mousePos) {
    for(auto& it: this->cards) {
	it.second->update(dt, mousePos);
    }
}

void CompDeck::render(sf::RenderTarget* target) {
    if(!this->cards.empty())
	this->cards.begin()->second->render(target);
    if(this->selected != "") {
	this->cards[this->selected]->render(target);
    }
}
