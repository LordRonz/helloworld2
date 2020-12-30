#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
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
//insisialisasi variable
void GameState::initVariables() {
    this->turn = std::vector<bool> (this->decks.size() - 2);
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
	std::printf("ERROR LOADING BG TEXTURE\n");
    this->bg.setTexture(&this->bgTexture);
}

//inisialisasi texture
void GameState::initTextures() {
    //if(!this->textures["2C"].loadFromFile("res/txrs/cards/2C.png"))
    //	printf("ERROR LOADING CARD TEXTURE\n");
    std::string path = "res/txrs/cards/";
    std::vector<std::string> crds{"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
    for(const std::string& c: crds) {
	if(!this->textures[c + "C"].loadFromFile(path + c + "C.png"))
	    std::printf("ERROR LOADING CARD TEXTURE\n");
	if(!this->textures[c + "H"].loadFromFile(path + c + "H.png"))
	    std::printf("ERROR LOADING CARD TEXTURE\n");
	if(!this->textures[c + "D"].loadFromFile(path + c + "D.png"))
	    std::printf("ERROR LOADING CARD TEXTURE\n");
	if(!this->textures[c + "S"].loadFromFile(path + c + "S.png"))
	    std::printf("ERROR LOADING CARD TEXTURE\n");

	//printf("%c\n", c);
    }
    if(!this->textures["BUTT"].loadFromFile("res/txrs/cards/blue_back.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
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
	    //this->decks[0]->addCard(new Card(it2.first, it1.first, &this->textures[it1.second + it2.second], &this->textures["BUTT"]));
	}
    }
    std::shuffle(tmp.begin(), tmp.end(), std::default_random_engine(std::random_device{}()));
    for(auto& crd: tmp) {
	this->decks[Player0]->addCard(crd);
    }
    //this->decks[0]->addCard(new Card(3, 2, &this->textures["2C"], &this->textures["BUTT"]));
    this->decks.push_back(new PlayerDeck(&this->decks));
    this->decks.push_back(new CompDeck(&this->decks));
    this->decks.push_back(new TrashDeck(&this->decks));
    //this->decks[1]->addCard(new Card(3, 3, &this->textures["3C"]));
}
//update
void GameState::update(const double& dt) {
    //std::printf("Hello GameState\n");
    this->updateMousePos();
    this->updateInput(dt);
    this->updateDecks(dt);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//std::printf("A\n");
}
//update tiap deck
void GameState::updateDecks(const double& dt) {
    //First move
    bool tmp = this->begin;
    if(this->decks[Player0]->getCardCount() > 39) {
	//int tmp = this->decks[Player0]->getCardCount();
	//this->decks[Player0]->passCard(this->passDeck, dt);
	//if(tmp != this->decks[Player0]->getCardCount()) {
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
	    std::fill(this->turn.begin(), this->turn.end(), true);
	}
    }
    else return;
    if(this->turn[Player2 - 1]) {
	this->updateComp(dt);
    }
    else if(this->turn[Player1 - 1]){
	this->updatePlayer(dt);
    }
}

const bool GameState::isValid(const int& selected) {
    if(this->begin && !this->cmpCards.empty())
	return this->cmpCards.front().second->getKind() == this->decks[Player1]->getKindAtIndex(selected);
    return false;
}

void GameState::compareCards() {
    if(this->firstMove) {
	
    }
}
//update comp
const bool GameState::updateComp(const double& dt) {
    if(this->turn[Player2 - 1] && this->decks[Player2]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player2]->getSelected() == -1)
	    this->decks[Player2]->artificialStupidity(this->cmpCards.front().second);
    	if(this->decks[Player2]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player2, this->decks[Player2]->getPassedCard()));
	    this->turn[Player2 - 1] = false;
	    this->decks[Player2]->reset();
	}
    }
    else if(!this->decks[Player2]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player0]->passCard(Player2, dt)) {
	    this->turn[Player2 - 1] = false;
	}
    }
    else {
	this->decks[Player2]->reset();
    }
    return false; 
}
//update player
const bool GameState::updatePlayer(const double& dt) {
    if(this->turn[Player1 - 1] && this->decks[Player1]->canMove(this->cmpCards.front().second->getKind()) && this->isValid(this->decks[Player1]->getSelected())) {
	if(this->decks[Player1]->passCard(Trash, dt)) {
	    this->cmpCards.push_back(std::make_pair(Player1, this->decks[Player1]->getPassedCard()));
	    this->turn[Player1 - 1] = false;
	    this->decks[Player1]->reset();
	}
    }

    else if(!this->decks[Player1]->canMove(this->cmpCards.front().second->getKind())) {
	if(this->decks[Player0]->passCard(Player1, dt)) {
	    this->turn[Player1 - 1] = false;
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
    //this->deck->render(target);
    target->draw(this->bg);
    for(auto& it: this->decks) {
	it->render(target);
    }
}

void GameState::updateInput(const double& dt) {
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//this->player->move(dt, 0.f, -1.f);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//this->player->move(dt, 0.f, 1.f);
}

void GameState::endState() {
    std::printf("Ending state\n");
}
