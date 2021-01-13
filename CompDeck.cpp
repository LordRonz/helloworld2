#include "CompDeck.h"

CompDeck::CompDeck(std::vector<Deck*>* decks, const float& x, const float& y) :Deck(decks, x, y) {
    //inti stuff
    this->selected = -1;
    this->initRandomEngine();
}
// cleanup
CompDeck::~CompDeck() {
    //biar ga memory leak, soalnya pointer card dynamically allocated dengan new
    for(auto& it: this->cards)
	delete it;
}

// inisialisasi random engine, buat dipakai di artificialStupidity
void CompDeck::initRandomEngine() {
    this->rng.seed(std::random_device{}());
}

//tambahin kartu
void CompDeck::addCard(Card* card) {
    // sama aja kayak playerDeck
    if(!card) return;
    ++this->cardCount;
    this->cards.push_back(card);
    //tapi ini posisinya sama semua
    this->cards.back()->setPosition(this->pos.x, this->pos.y);
}

//return passedCard ptr
Card* CompDeck::getPassedCard() {
    return this->passedCard;
}

//algoritma buat memilih kartu
void CompDeck::artificialStupidity(Card* card) {
    // kalo vector cards kosong ya return
    if(this->cards.empty()) return;
    // kalo pointer cardnya nullptr, pilih kartu random
    if(!card) {
	std::uniform_int_distribution<> res(0, this->cards.size() - 1);
	this->selected = res(this->rng);
	return;
    }
    // kalo ga ya pilih yang optimal
    // jika ada kartu yang sejenis, tapi ga punya yang nilainya lebih besar, pilih kartu
    // sejenis yang terkecil. Tapi kalo ada yang nilainya lebih besar, pilih yang terkecil
    // misal, lawan ngasi 4D (card pointernya punya nilai 4 dan jenis diamond), deck ini punya 5D
    // dan 10D, pilih 5D. Kalo deck ini cuma punya 2D sama 3D, pilih 2D
    unsigned mnIndexFound(0), mnFound(15), mnIndexNotFound(0), mnNotFound(15);
    bool found{};
    for(unsigned i = 0, j = this->cards.size(); i < j; ++i) {
	// kalo pointer cardnya null, continue ke iterasi selanjutnya
	if(!this->cards[i]) continue;
	// jika kartu di vector decks pada index ke i jenisnya sama dengan pointer card...
	if(this->cards[i]->getKind() == card->getKind()) {
	    unsigned tmp(0);
	    // jika nilai kartu ke i ini lebih besar dari nilai pointer card
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
    // ternary operation
    // if found, return mnIndexFound, otherwise return mxIndexNotFound
    this->selected = found ? mnIndexFound : mnIndexNotFound;
}

//oper kartu
bool CompDeck::passCard(const unsigned int& trgt, const double& dt) {
    if(!this->cards.empty() && this->selected < this->cards.size() && this->cards[this->selected]) {
	this->passedCard = this->cards[this->selected];
	if(vectorDistance(this->cards[this->selected]->getPosition(), (*this->decks)[trgt]->getPosition()) > 20.f) {
	    // kalo masuk sini berarti belum nyampe, gerakkin spritenya pake some maffs
	    this->cards[this->selected]->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    //nyampe, oper pointer
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

//return selected card index
int CompDeck::getSelected() {
    return this->selected;
}

//cek apa bisa bergerak
bool CompDeck::canMove(const unsigned int& kind) {
    for(auto& it: this->cards) {
	if(it && it->getKind() == kind) return true;
    }
    return false;
}

//reset
void CompDeck::reset() {
    this->selected = -1;
    this->passedCard = nullptr;
}

//update kosong aja, karena sebenernya cuma update input jg
void CompDeck::update(const double& dt, const sf::Vector2f& mousePos) {

}

//render
void CompDeck::render(sf::RenderTarget* target) {
    if(!target || this->cards.empty()) return;
    unsigned i = 0;
    for(; this->selected == i && i < this->cards.size() - 1; ++i);
    if(this->cards[i])
        this->cards[i]->render(target);
    if(this->selected != -1 && this->cards[this->selected])
        this->cards[this->selected]->render(target);
}
