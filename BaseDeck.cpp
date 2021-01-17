#include "BaseDeck.h"

BaseDeck::BaseDeck(std::vector<Deck*>* decks, const float& x, const float& y, sf::Font* font) : Deck(decks, x, y, font) {
    // self explanatory
}

// bersih-bersih
BaseDeck::~BaseDeck() {
    while(!this->cards.empty()) {
	//hapus tiap card, biar ga memory leak
	delete this->cards.top();
	this->cards.pop();
    }
    // dummynya dihapus juga dong !
    delete this->dummy;
}

//nambah kartu ke stack
void BaseDeck::addCard(Card* card) {
    //jika pointer card adalah null, return, ya emang siapa yang mau nyimpen nullptr, bahaya bos
    if(!card) return;

    //apabila jumlah kartu == 0, dalam artian kosong, maka tambah kartu ke dummy, selain itu ya
    //dipush ke stack

    if(!card->isButt()) card->flip();
    if(!this->cardCount++) {
        this->dummy = card;
        this->dummy->setPosition(this->pos.x, this->pos.y);
        return;
    }
    this->cards.push(card);
    this->cards.top()->setPosition(this->pos.x, this->pos.y);
}

void BaseDeck::update(const double& dt, const sf::Vector2f& mousePos) {
}

// render kartu yang ada di stack paling atas, dan dummynya biat saat ngepass kartunya ga ilang dari
// deck
void BaseDeck::render(sf::RenderTarget* target) {
    if(!target) return;
    if(!this->cards.empty()) {
	//cuma render kartu paling atas
        if(this->cards.top())
	    this->cards.top()->render(target);
	//dummynya
        if(this->dummy)
	   this->dummy->render(target);
    }
}

// dapatkan pointer card yang sedang dikasihkan ke deck lain
Card* BaseDeck::getPassedCard() {
    return this->passedCard;
}


//memberikan kartu ke deck lainnya, kalo udah nyampe return true, kalo belom return false
bool BaseDeck::passCard(const unsigned int& trgt, const double& dt) {
    // karena kumpulan kartu di deck ini menggunakan stack, maka hanya dapat diakses pointer card
    // yang terdapat di atas tumpukan (top), maka setiap kartu yang dioper adalah kartu yang ada di
    // top()
    if(!this->cards.empty() && this->cards.top()) {
	this->passedCard = this->cards.top();
	if(vectorDistance(this->cards.top()->getPosition(), (*this->decks)[trgt]->getPosition()) > 20.f) {
	    //disini cuma menggerakkan sprite cardnya, blum memindah pointernya
	    this->cards.top()->move(dt, (*this->decks)[trgt]->getPosition().x, (*this->decks)[trgt]->getPosition().y);
	}
	else {
	    //kalo masuk kesini, brarti udah nyampe, saatnya memindahkan pointer cardnya
	    (*this->decks)[trgt]->addCard(this->cards.top());
	    this->cards.pop();
	    --this->cardCount;
	    return true;
	}
    }
    // supaya yang manggil fungsi ini tau kalo kartu udh nyampe di tujuan
    return false;
}
