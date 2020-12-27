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
    if(!this->textures["2C"].loadFromFile("res/txrs/cards/2C.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["2H"].loadFromFile("res/txrs/cards/2H.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["2D"].loadFromFile("res/txrs/cards/2D.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["2S"].loadFromFile("res/txrs/cards/2S.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["3C"].loadFromFile("res/txrs/cards/3C.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["3H"].loadFromFile("res/txrs/cards/3H.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["3D"].loadFromFile("res/txrs/cards/3D.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["3S"].loadFromFile("res/txrs/cards/3S.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
}

void GameState::initDecks() {
    this->decks.push_back(new BaseDeck(&this->decks));
    this->decks[0]->addCard(new Card(3, 2, &this->textures["2C"]));
    this->decks[0]->addCard(new Card(2, 2, &this->textures["2H"]));
    this->decks[0]->addCard(new Card(4, 2, &this->textures["2S"]));
    this->decks[0]->addCard(new Card(1, 2, &this->textures["2D"]));
    this->decks[0]->addCard(new Card(3, 3, &this->textures["3C"]));
    this->decks[0]->addCard(new Card(2, 3, &this->textures["3H"]));
    this->decks[0]->addCard(new Card(4, 3, &this->textures["3S"]));
    this->decks.push_back(new PlayerDeck(&this->decks));
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
