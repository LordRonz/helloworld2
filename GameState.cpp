#include "GameState.h"

GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
    this->initTextures();
    this->initDecks();
}

GameState::~GameState() {
    for(auto& it: this->decks) {
	delete it;
    }
    decks = std::vector<Deck*>();
    //delete this->deck;
}

void GameState::initTextures() {
    //if(!this->textures["2C"].loadFromFile("res/txrs/cards/2C.png"))
    //	printf("ERROR LOADING CARD TEXTURE\n");
    std::string path = "res/txrs/cards/";
    std::vector<std::string> crds{"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    for(const std::string& c: crds) {
	if(!this->textures[c + "C"].loadFromFile(path + c + "C.png"))
	    printf("ERROR LOADING CARD TEXTURE\n");
	if(!this->textures[c + "H"].loadFromFile(path + c + "H.png"))
	    printf("ERROR LOADING CARD TEXTURE\n");
	if(!this->textures[c + "D"].loadFromFile(path + c + "D.png"))
	    printf("ERROR LOADING CARD TEXTURE\n");
	if(!this->textures[c + "S"].loadFromFile(path + c + "S.png"))
	    printf("ERROR LOADING CARD TEXTURE\n");

	//printf("%c\n", c);
    }
    if(!this->textures["BUTT"].loadFromFile("res/txrs/cards/blue_back.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
}

void GameState::initDecks() {
    this->decks.push_back(new BaseDeck(&this->decks));
    std::map<int, std::string> knd {
	{1, "D"},
	{2, "H"},
	{3, "C"},
	{4, "S"}
    };
    std::map<int, std::string> val {
	{1, "A"},
	{2, "2"},
	{3, "3"},
	{4, "4"},
	{5, "5"},
	{6, "6"},
	{7, "7"},
	{8, "8"},
	{9, "9"},
	{10, "10"},
	{11, "J"},
	{12, "Q"},
	{13, "K"}
    };
    this->decks[0]->addCard(new Card(0, 0, &this->textures["BUTT"], &this->textures["BUTT"]));
    std::vector<Card*> tmp;
    for(auto& it1: val) {
	for(auto& it2 : knd) {
	    tmp.push_back(new Card(it2.first, it1.first, &this->textures[it1.second + it2.second], &this->textures["BUTT"]));
	    //this->decks[0]->addCard(new Card(it2.first, it1.first, &this->textures[it1.second + it2.second], &this->textures["BUTT"]));
	}
    }
    std::shuffle(tmp.begin(), tmp.end(), std::default_random_engine(std::random_device{}()));
    for(auto& crd: tmp) {
	this->decks[0]->addCard(crd);
    }
    //this->decks[0]->addCard(new Card(3, 2, &this->textures["2C"], &this->textures["BUTT"]));
    this->decks.push_back(new PlayerDeck(&this->decks));
    this->decks.push_back(new CompDeck(&this->decks));
    //this->decks[1]->addCard(new Card(3, 3, &this->textures["3C"]));
}

void GameState::update(const double& dt) {
    //std::printf("Hello GameState\n");
    this->updateMousePos();
    this->updateInput(dt);
    for(auto& it: this->decks) {
	it->update(dt, this->mousePosView);
    }
    //this->deck->update(dt, this->mousePosView);
    //printf("%f %f\n", this->mousePosView.x, this->mousePosView.y);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//std::printf("A\n");
}

void GameState::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    //this->deck->render(target);
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
