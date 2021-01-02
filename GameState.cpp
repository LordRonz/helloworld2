#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
    this->initRenderTexture();
    this->initBackground();
    this->initTextures();
    this->initDecks();
    this->initVariables();
}

GameState::~GameState() {
    for(auto& it: this->decks) {
	delete it;
    }
}

void GameState::initRenderTexture() {
    this->renderTexture.create(1280.f, 720.f);
    this->renderSprite.setTexture(this->renderTexture.getTexture());
}

//insisialisasi variable
void GameState::initVariables() {

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
    this->decks.push_back(new BaseDeck(&this->decks));
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
    this->decks[0]->addCard(new Card(static_cast<unsigned short>(0), static_cast<unsigned short>(0), &this->textures["BUTT"], &this->textures["BUTT"]));
    std::vector<Card*> tmp;
    for(auto& it1: val) {
	for(auto& it2 : knd) {
	    tmp.push_back(new Card(it2.first, it1.first, &this->textures[it1.second + it2.second], &this->textures["BUTT"]));
	}
    }
    std::shuffle(tmp.begin(), tmp.end(), std::default_random_engine(std::random_device{}()));
    for(auto& crd: tmp) {
	this->decks[Player0]->addCard(crd);
    }
    this->decks.push_back(new PlayerDeck(&this->decks));
    this->decks.push_back(new CompDeck(&this->decks));
    this->decks.push_back(new TrashDeck(&this->decks));
}

//update
void GameState::update(const double& dt) {
    this->updateMousePos();
    this->updateInput(dt);
    this->updateDecks(dt);
}

//update tiap deck
void GameState::updateDecks(const double& dt) {
    //First move
    bool tmp = this->begin;
    if(this->decks[Player0]->getCardCount() > 39) {
	if(this->decks[Player0]->passCard(this->passDeck, dt)) {
	    ++this->passDeck;
	    this->passDeck = this->passDeck == Trash ? 1 : this->passDeck;
	}
    }
    else if(!this->begin) {
    	if(this->decks[Player0]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player0, this->decks[Player0]->getPassedCard()));
	    this->begin = true;
	}
    }

    if(this->begin) {
	for(auto& it: this->decks) {
	    it->update(dt, this->mousePosView);
	}
	if(!tmp) {
	    this->turn.set();
	}
    }
    else return;

    if(this->turn[Player2 - 1]) {
	this->updateComp(dt);
    }
    else if(this->turn[Player1 - 1]){
	this->updatePlayer(dt);
    }

    if(this->turn.none()) {
	if(this->winner == -1)
	    this->compareCards();
	if(this->decks[Trash]->passCard(69, dt)) {
	    this->cmpCards.clear();
	    this->turn.reset();
	    this->turn[winner] = true;
	    this->winner = -1;
	    if(this->firstMove) this->firstMove = false;
	}
    }
}

const bool GameState::isValid(const int& selected) {
    if(this->begin && !this->cmpCards.empty())
	return this->cmpCards.front().second->getKind() == this->decks[Player1]->getKindAtIndex(selected);
    return false;
}

void GameState::compareCards() {
    if(this->firstMove && this->cmpCards.size() == 1) {
	this->winner = Player2 - 1;
	return;
    }
    unsigned maxIndex = 0;
    int maxVal = -1;
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
const bool GameState::updateComp(const double& dt) {
    //kondisi jika player ini yang mulai duluan
    if(this->turn[Player2 - 1] && this->cmpCards.empty()) {
	if(this->decks[Player2]->getSelected() == -1) {
	    this->decks[Player2]->artificialStupidity(nullptr);
	}
	if(this->decks[Player2]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player2, this->decks[Player2]->getPassedCard()));
	    this->turn[Player2 - 1] = false;
	    this->turn[Player1 - 1] = true;
	    this->decks[Player2]->reset();
	}
    }

    //kondisi jika player ini tidak mulai duluan
    else if(this->turn[Player2 - 1] && this->decks[Player2]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player2]->getSelected() == -1)
	    this->decks[Player2]->artificialStupidity(this->cmpCards.front().second);
    	if(this->decks[Player2]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player2, this->decks[Player2]->getPassedCard()));
	    this->turn[Player2 - 1] = false;
	    this->decks[Player2]->reset();
	}
    }

    else if(!this->cmpCards.empty() && !this->decks[Player2]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player0]->passCard(Player2, dt)) {
	    this->turn[Player2 - 1] = false;
	    this->decks[Player2]->reset();
	}
    }
    else {
	this->decks[Player2]->reset();
    }
    return false; 
}

//update player
const bool GameState::updatePlayer(const double& dt) {
    if(this->turn[Player1 - 1] && this->cmpCards.empty()) {
	if(this->decks[Player1]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player1, this->decks[Player1]->getPassedCard()));
	    this->turn[Player1 - 1] = false;
	    this->turn[Player2 - 1] = true;
	    this->decks[Player1]->reset();
	}
    }

    else if(this->turn[Player1 - 1] && this->decks[Player1]->canMove(this->cmpCards.front().second->getKind()) && this->isValid(this->decks[Player1]->getSelected())) {
	if(this->decks[Player1]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player1, this->decks[Player1]->getPassedCard()));
	    this->turn[Player1 - 1] = false;
	    this->decks[Player1]->reset();
	}
    }

    else if(!this->cmpCards.empty() && !this->decks[Player1]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player0]->passCard(Player1, dt)) {
	    this->turn[Player1 - 1] = false;
	    this->decks[Player1]->reset();
	}
	else {
	}
    }
    else {
	this->decks[Player1]->reset();
    }
    return false;
}

void GameState::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    this->renderTexture.clear();
    this->renderTexture.draw(this->bg);
    for(auto& it: this->decks) {
	if(it)
	    it->render(&this->renderTexture);
    }
    this->renderTexture.display();
    target->draw(this->renderSprite);
}

void GameState::updateInput(const double& dt) {
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//this->player->move(dt, 0.f, -1.f);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//this->player->move(dt, 0.f, 1.f);
}

