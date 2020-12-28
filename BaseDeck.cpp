#include "BaseDeck.h"

BaseDeck::BaseDeck(std::vector<Deck*>* decks) : Deck(decks) {
    this->setPosition(10.f, 10.f);
}

BaseDeck::~BaseDeck() {
    while(!this->cards.empty()) {
	delete this->cards.top();
	this->cards.pop();
    }
}

void BaseDeck::addCard(Card* card) {
    if(!this->cardCount++) {
	this->dummy = card;
	this->dummy->setPosition(this->pos.x, this->pos.y);
	return;
    }
    std::printf("%d\n", cardCount);
    this->cards.emplace(card);
    this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void BaseDeck::update(const double& dt, const sf::Vector2f mousePos) {
    if(!this->cards.empty()) {
    	this->cards.top()->update(dt, mousePos);
    }    
    
    if(this->cardCount > 39) {
	float dist = std::sqrt(
	    std::pow((this->cards.top()->getPosition().x - (*this->decks)[this->passDeck]->getPosition().x), 2) + 
	    std::pow((this->cards.top()->getPosition().y - (*this->decks)[this->passDeck]->getPosition().y), 2));
	//std::printf("%f\n", dist);
	//system("cls");
	//std::printf("%f\n", (*this->decks)[this->passDeck]->getPosition().x);
	if(dist > 20.f) {
	    this->cards.top()->move(dt, (*this->decks)[this->passDeck]->getPosition().x, (*this->decks)[this->passDeck]->getPosition().y);
	}
	else {
	    this->passCard();
	}
    }
}

void BaseDeck::render(sf::RenderTarget* target) {
    if(!this->cards.empty())
	this->cards.top()->render(target);

    this->dummy->render(target);
}

void BaseDeck::passCard() {
    if(!this->cards.empty()) {
	if(this->passDeck == Player1) this->cards.top()->flip();
	(*this->decks)[this->passDeck++]->addCard(this->cards.top());
	this->cards.pop();
	this->passDeck = this->passDeck == decks->size() ? 1 : this->passDeck;
	--this->cardCount;
    } 
}
