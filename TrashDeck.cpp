#include "TrashDeck.h"

TrashDeck::TrashDeck(std::vector<Deck*>* decks, const float& x, const float& y) : Deck(decks, x, y)  {
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
    this->cards.push_back(card);
    //atur posisi
    this->rearrange();
}

// passCard disini gunanya sebenarnya buang smua kartu
bool TrashDeck::passCard(const unsigned int& trgt, const double& dt) {
    return this->throwDeck(dt);
}

// buang kartu
bool TrashDeck::throwDeck(const double& dt) {
    if(this->cards.empty()) return true;
    for(auto& it: this->cards) {
	// jika suatu pointer kartu dalam vector null, lanjut iterasi berikutnya
	if(!it) continue;
	// kalo belum sampe, gerakin kartunya kearah pojok
	if(vectorDistance(it->getPosition(), sf::Vector2f(1290.f, 360.f)) > 20.f)
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
    if(!this->cardCount) {
	//std::puts("Cleared");
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

// not used
void TrashDeck::update(const double& dt, const sf::Vector2f& mousePos) {

}

//render
void TrashDeck::render(sf::RenderTarget* target) {
    if(!target) return;
    for(auto& it: this->cards) {
        if(it)
	   it->render(target);
    }
}
