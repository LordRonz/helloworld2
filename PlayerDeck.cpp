#include "PlayerDeck.h"

PlayerDeck::PlayerDeck(std::vector<Deck*>* decks, const float& x, const float& y) : Deck(decks, x, y), selected(-1) {
    //init
}

//bersih bersih
PlayerDeck::~PlayerDeck() {
    for(auto& it: this->cards)
	delete it;
}

//tambah kartu
void PlayerDeck::addCard(Card* card) {
    //seperti biasa, cek apakah kartu nullptr, bahaya kalo nyimpen nullptr
    if(!card) return;
    //untuk tiap kartu ditambahkan, increment cardCount
    ++this->cardCount;
    this->cards.push_back(card);
    this->rearrange();
}

// return pointer kartu yang dioper
Card* PlayerDeck::getPassedCard() {
    return this->passedCard;
}

// return kind at specified index
unsigned short PlayerDeck::getKindAtIndex(const int& index) {
    return index >= 0 && index < static_cast<int>(this->cards.size()) && this->cards[index] ? this->cards[index]->getKind() : -1;
}

// oper kartu ke deck lain
bool PlayerDeck::passCard(const unsigned int& trgt, const double& dt) {
    if(this->selected == -1) return false;
    if(!this->cards.empty() && this->selected < static_cast<int>(this->cards.size()) && this->cards[this->selected]) {
	this->passedCard = this->cards[this->selected];

	if(vectorDistance(this->cards[this->selected]->getPosition(), (*this->decks)[trgt]->getPosition()) > 20.f) {
	    // masih gerakin spritenya, pointer masih di sini
	    this->cards[this->selected]->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    //kalo masuk sini, brarti kartu sudah sampai dan saatnya mengoper card pointer
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

//update all cards in this deck
void PlayerDeck::update(const double& dt, const sf::Vector2f& mousePos) {
    for(unsigned i = 0, j = this->cards.size(); i < j; ++i) {
	if(!this->cards[i]) continue;
	this->cards[i]->update(dt, mousePos);
	if(this->selected == -1 && this->cards[i]->isClicked())
	    this->selected = i;
    }
}

// reset selected and passed card
void PlayerDeck::reset() {
    //supaya dianggap deck ini sedang tidak memilih kartu
    this->selected = -1;
    //reset passedCard ptr
    this->passedCard = nullptr;
}

// cek apa bisa gerak
bool PlayerDeck::canMove(const unsigned int& kind) {
    //iterate through cards vector
    for(auto& it: this->cards) {
	if(it && it->getKind() == kind) return true;
    }
    return false;
}


//rapikan posisi kartu
void PlayerDeck::rearrange() {
    unsigned i = 1;
    // maff stuff
    for(auto& it: this->cards) {
	if(it)
	    it->setPosition((1160.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
}
//render
void PlayerDeck::render(sf::RenderTarget* target) {
    //cek apakah target null, kalo null return
    if(!target) return;
    for(auto& it: this->cards) {
        if(it)
	    it->render(target);
    }
}

//return selected card index
int PlayerDeck::getSelected() {
    return this->selected;
}
