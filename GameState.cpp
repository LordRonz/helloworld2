#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
    //fungsi-fungsi buat inisialisasi dicall smua disini, biar rapih
    this->initRenderTexture();
    this->initBackground();
    this->initTextures();
    this->initDecks();
    this->initFonts();
    this->initPause();
    this->initEndGame();
}

//bersih-bersih
GameState::~GameState() {
    delete this->endGame;
    for(auto& it: this->decks) {
	delete it;
    }
}

//rendertexture itu semacam kanvas tapi belum ditampilkan di layar, dirender di gpu, jadi nanti
//tinggal digabung dan digambar sekali ke layar
void GameState::initRenderTexture() {
    this->renderTexture.create(this->window->getSize().x, this->window->getSize().y);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
}

//inisialisasi font
void GameState::initFonts() {
    if(!this->font.loadFromFile("res/fonts/lhf_american_sans.ttf"))
	std::puts("ERROR LOADING FONT");
}

// endgame ni blum jadi
void GameState::initEndGame() {
    this->endGame = new EndGame(&this->font);
}

void GameState::initPause() {
    this->pMenu = new PauseMenu(this->window, &this->font);
    float width = 0.13f * this->window->getSize().x;
    float height = 0.06f * this->window->getSize().y;
    float y = 0.74f * this->window->getSize().y;
    this->pMenu->addButton("QUIT", y, width, height, 30, "Quit");
}

//inisialisasi background
void GameState::initBackground() {
    this->bg.setSize(
	sf::Vector2f
    	(
	    static_cast<float>(this->window->getSize().x),
	    static_cast<float>(this->window->getSize().y)
	)
    );

    if(!this->bgTexture.loadFromFile("res/txrs/bg/bg.png"))
	std::puts("ERROR LOADING BG TEXTURE");
    this->bg.setTexture(&this->bgTexture);
}

//inisialisasi texture
void GameState::initTextures() {
    //daripada ngetik 1 1 load fromfilenya, karena texturenya banyak pake for loop dan string
    //concatenation biar pendek
    std::string path = "res/txrs/cards/";
    std::vector<std::string> crds{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    for(const std::string& c: crds) {
	if(!this->textures[c + "C"].loadFromFile(path + c + "C.png"))
	    std::puts("ERROR LOADING CARD TEXTURE");
	if(!this->textures[c + "H"].loadFromFile(path + c + "H.png"))
	    std::puts("ERROR LOADING CARD TEXTURE");
	if(!this->textures[c + "D"].loadFromFile(path + c + "D.png"))
	    std::puts("ERROR LOADING CARD TEXTURE");
	if(!this->textures[c + "S"].loadFromFile(path + c + "S.png"))
	    std::puts("ERROR LOADING CARD TEXTURE");
    }
    if(!this->textures["BUTT"].loadFromFile("res/txrs/cards/blue_back.png"))
	std::puts("ERROR LOADING CARD TEXTURE");
}

//inisialisasi deck
void GameState::initDecks() {
    //deck bandar diinisialisasi
    this->decks.push_back(new BaseDeck(&this->decks, 10.f, 10.f, &this->font));
    //same trick as initTextures
    std::map<unsigned short, std::string> knd {
	{1, "D"},
	{2, "H"},
	{3, "C"},
	{4, "S"}
    };

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
    //ini dummycard buat deck bandar
    this->decks[0]->addCard(new Card(static_cast<unsigned short>(0), static_cast<unsigned short>(0), &this->textures["BUTT"], &this->textures["BUTT"]));

    //vector biar praktis aja sih, kayak initTextures, kalo ga panjang bgt, sama biar gampang
    //ngocoknya
    std::vector<Card*> tmp;
    for(auto& it1: val) {
	for(auto& it2 : knd)
	    tmp.push_back(new Card(it2.first, it1.first, &this->textures[it1.second + it2.second], &this->textures["BUTT"]));
    }
    //ngocok
    std::shuffle(tmp.begin(), tmp.end(), std::default_random_engine(std::random_device{}()));
    //habis dikocok, smua card ditaro di BaseDeck
    for(auto& crd: tmp)
	this->decks[Player0]->addCard(crd);
    //inisialisasi deck2 lain
    this->decks.push_back(new PlayerDeck(&this->decks, 500.f, 500.f, &this->font));
    this->decks.push_back(new CompDeck(&this->decks, 600.f, 10.f, &this->font));
    this->decks.push_back(new TrashDeck(&this->decks, 500.f, 240.f, &this->font));
}

//update
void GameState::update(const double& dt) {
    // update posisi mouse
    this->updateMousePos();
    this->updateInput(dt);
    //cek kalo ada yang menang
    if(!this->paused) {
	if(!this->someoneWon)
	    this->updateDecks(dt);
	else
	    this->updateEndGame(dt);
    }
    else {
	this->pMenu->update(this->mousePosView);
	this->updatePauseMenuButtons();
    }
}

void GameState::updatePauseMenuButtons() {
    if(this->pMenu->isButtonPressed("QUIT"))
        this->endState();
}

//update tiap deck
void GameState::updateDecks(const double& dt) {
    //First move
    // ini bagian dimana si bandar ngebagi kartu ke tiap pemain
    bool tmp = this->begin;
    if(this->decks[Player0]->getCardCount() > 39) {
	if(this->decks[Player0]->passCard(this->passDeck, dt)) {
	    ++this->passDeck;
	    this->passDeck = this->passDeck == Trash ? 1 : this->passDeck;
	}
    }
    else if(!this->begin) {
    	if(this->decks[Player0]->passCard(Trash, dt)) {
	    //cmpcards ini vector yang isinya kartu2 yang mau dicompare, pake pair biar tau ini
	    //kartunya punya siapa
	    this->cmpCards.push_back(std::make_pair(Player0, this->decks[Player0]->getPassedCard()));
	    this->begin = true;
	}
    }

    if(this->begin) {
	for(auto& it: this->decks)
	    it->update(dt, this->mousePosView);
	//turn ini adalah bitset, simplenya array boolean lah, set akan mengatur semua boolean
	//menjadi true
	if(!tmp)
	    this->turn.set();
    }
    else return;
    
    //cek apakah salah satu deck pemain kosong, kalo iya berarti cek siapa yang menang
    for(unsigned i = 1, j = this->decks.size() - 1; i < j; ++i) {
	if(this->decks[i]->getCardCount() == 0) {
	    this->someoneWon = true;
	    if(i == Player1) this->endGame->setText("YOU WIN");
	    else this->endGame->setText("YOU LOSE");
	    return;
	}
    }

    //kalo giliran player selain manusia
    if(this->turn[Player2 - 1])
	this->updateComp(dt);
    
    //giliran player manusia
    else if(this->turn[Player1 - 1])
	this->updatePlayer(dt);

    //kalo semua turn false, saatnya membandingkan siapa yang terbesar nilainya dengan method
    //compareCards
    if(this->turn.none()) {
	//kalo pemenangnya belum ditentukan, panggil method compareCards
	//kenapa pake if, biar ga berkali2 call method
	if(this->winner == -1)
	    this->compareCards();
	if(this->decks[Trash]->passCard(69, dt)) {
	    //kalo masuk sini, brarti deck sudah dibuang, saatnya mengatur giliran dll
	    this->cmpCards.clear();
	    this->turn.reset();
	    this->turn[winner] = true;
	    this->winner = -1;
	    if(this->firstMove) this->firstMove = false;
	}
    }
}

void GameState::updateEndGame(const double& dt) {
    this->endGame->update(this->mousePosView);
}

// cek apakah si player manusia ini memilih kartu yang jenisnya valid
const bool GameState::isValid(const int& selected) const{
    if(this->begin && !this->cmpCards.empty())
	return this->cmpCards.front().second->getKind() == this->decks[Player1]->getKindAtIndex(selected);
    return false;
}

// tentukan pemenang
void GameState::compareCards() {
    if(this->firstMove && this->cmpCards.size() == 1) {
	this->winner = Player2 - 1;
	return;
    }
    unsigned maxIndex = 0, maxVal = 0;

    for(unsigned i = this->firstMove ? 1 : 0, j = this->cmpCards.size(); i < j; ++i) {
	if(!this->cmpCards[i].second) continue;
        int tmp;
        if((tmp = this->cmpCards[i].second->getVal()) > maxVal) {
	   maxVal = tmp;
	   maxIndex = i;
        }
    }
    this->winner = this->cmpCards[maxIndex].first - 1;
}

//update comp
bool GameState::updateComp(const double& dt) {
    //kondisi jika player ini yang mulai duluan
    if(this->turn[Player2 - 1] && this->cmpCards.empty()) {
	//kalo si deck computer belum milih kartu, ya suruh pilih menggunakan artificialStupidity
	if(this->decks[Player2]->getSelected() == -1)
	    this->decks[Player2]->artificialStupidity(nullptr);

	if(this->decks[Player2]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player2, this->decks[Player2]->getPassedCard()));
	    this->turn[Player2 - 1] = false;
	    this->turn[Player1 - 1] = true;
	    this->decks[Player2]->reset();
	}
    }

    //kondisi jika player ini tidak mulai duluan
    else if(this->turn[Player2 - 1] && this->decks[Player2]->canMove(this->cmpCards.front().second->getKind())) {
	//ya artificial stupidity
	if(this->decks[Player2]->getSelected() == -1)
	    this->decks[Player2]->artificialStupidity(this->cmpCards.front().second);
    	if(this->decks[Player2]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player2, this->decks[Player2]->getPassedCard()));
	    this->turn[Player2 - 1] = false;
	    this->decks[Player2]->reset();
	}
    }
    // gabisa gerak, ambil kartu dari bandar
    else if(!this->cmpCards.empty() && !this->decks[Player2]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player0]->getCardCount() > 1) {
	    if(this->decks[Player0]->passCard(Player2, dt)) {
		this->decks[Player2]->reset();
	    }
	}
	else {
	    unsigned tmp = this->cmpCards.front().first;
	    if(this->decks[Trash]->passCard(Player2, dt)) {
		this->decks[Player2]->reset();
		this->turn.reset();
		this->turn[tmp - 1] = true;
	    }
	}
    }
    else
	this->decks[Player2]->reset();
    return false; 
}

//update player manusia
bool GameState::updatePlayer(const double& dt) {

    //giliran player, karena menang round sebelumnya
    if(this->turn[Player1 - 1] && this->cmpCards.empty()) {
	if(this->decks[Player1]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player1, this->decks[Player1]->getPassedCard()));
	    this->turn[Player1 - 1] = false;
	    this->turn[Player2 - 1] = true;
	    this->decks[Player1]->reset();
	}
    }
    // counter
    else if(this->turn[Player1 - 1] && this->decks[Player1]->canMove(this->cmpCards.front().second->getKind()) && this->isValid(this->decks[Player1]->getSelected())) {
	if(this->decks[Player1]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player1, this->decks[Player1]->getPassedCard()));
	    this->turn[Player1 - 1] = false;
	    this->decks[Player1]->reset();
	}
    }
    // ga bisa gerak, ambil kartu di bandar
    else if(!this->cmpCards.empty() && !this->decks[Player1]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player0]->getCardCount() > 1) {
	    if(this->decks[Player0]->passCard(Player1, dt)) {
		this->decks[Player1]->reset();
	    }
	}
	else {
	    unsigned tmp = this->cmpCards.front().first;
	    if(this->decks[Trash]->passCard(Player1, dt)) {
		this->decks[Player1]->reset();
		this->turn.reset();
		this->turn[tmp - 1] = true;
	    }
	}
    }
    else
	this->decks[Player1]->reset();
    return false;
}
// render stuff
void GameState::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    this->renderTexture.clear();
    this->renderTexture.draw(this->bg);
    for(auto& it: this->decks) {
	if(it)
	    it->render(&this->renderTexture);
    }
    if(this->someoneWon) this->endGame->render(&this->renderTexture);
    else if(this->paused && this->pMenu) {
	this->pMenu->render(&this->renderTexture);
    }
    this->renderTexture.display();
    target->draw(this->renderSprite);
}


// input
void GameState::updateInput(const double& dt) {
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//this->player->move(dt, 0.f, -1.f);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//this->player->move(dt, 0.f, 1.f);
    this->isEscPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);
    
    if(!this->isEscPressed && this->wasEscPressed) {
	this->paused ? this->unpauseState() : this->pauseState();
    }

    this->wasEscPressed = this->isEscPressed;
}
