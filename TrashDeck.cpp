#include "TrashDeck.h"

TrashDeck::TrashDeck(std::vector<Deck*>* decks, const float& x, const float& y, sf::Font* font) : Deck(decks, x, y, font)  {
}

//cleanup
TrashDeck::~TrashDeck() {
    for(auto& it: this->cards)
	delete it;
}

//nambah kartu
void TrashDeck::addCard(Card* card) {
    if(!card) return;
    ++this->cardCount;
    if(card->isButt()) card->flip();
    this->cards.push_back(card);
    //atur posisi
    this->rearrange();
}

// passCard disini gunanya sebenarnya buang smua kartu
bool TrashDeck::passCard(const unsigned int& trgt, const double& dt) {
    if(trgt > Trash)
	return this->throwDeck(dt);

    if(!this->cards.empty() && this->cards[0]) {
	if(VectorMath::vectorDistance(this->cards[0]->getPosition(), (*this->decks)[trgt]->getPosition()) > 20.f) {
	    // masih gerakin spritenya, pointer masih di sini
	    this->cards[0]->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    //kalo masuk sini, brarti kartu sudah sampai dan saatnya mengoper card pointer
	    (*this->decks)[trgt]->addCard(this->cards[0]);
	    this->cards.erase(this->cards.begin() + 0);
	    --this->cardCount;
	    this->rearrange();
	    return true;
	}
    }
    return false;
}

// buang kartu
bool TrashDeck::throwDeck(const double& dt) {
    if(this->cards.empty()) return true;
    for(auto& it: this->cards) {
	// jika suatu pointer kartu dalam vector null, lanjut iterasi berikutnya
	if(!it) continue;
	// kalo belum sampe, gerakin kartunya kearah pojok
	if(VectorMath::vectorDistance(it->getPosition(), sf::Vector2f(1290.f, 360.f)) > 20.f)
	    it->move(dt, 1290.f, 360.f);
	else {
	    //masuk sini, brarti udh nyampe, hapus kartu, atur pointernya jadi null supaya bisa
	    //dihindari
	    delete it;
	    it = nullptr;
	    --this->cardCount;
	}
    }
    // jika jumlah kartunya 0, hapus semua pointer di vector
    // note: yang dihapus pointernya bukan allocated datanya
    if(!this->cardCount) { // sama aja kayak this->cardCount == 0
	this->cards.clear();
    }
    return !this->cardCount;
}

//atur posisi
void TrashDeck::rearrange() {
    unsigned i = 1;
    for(auto& it: this->cards) {
	if(it)
	    it->setPosition((1160.f / (this->cardCount + 1)) * i++, this->pos.y);
    }
}


//render
void TrashDeck::render(sf::RenderTarget* target) {
    if(!target) return;
    for(auto& it: this->cards) {
        if(it)
	   it->render(target);
    }
}
