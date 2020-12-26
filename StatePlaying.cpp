#include "StatePlaying.h"

StatePlaying::StatePlaying(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
    this->initTextures();
    this->initDecks();
}

StatePlaying::~StatePlaying() {
    for(auto& it: this->decks) {
	delete it;
    }
    decks = std::vector<Deck*>();
    //delete this->deck;
}

void StatePlaying::initTextures() {
    if(!this->textures["2C"].loadFromFile("res/txrs/cards/2C.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["2H"].loadFromFile("res/txrs/cards/2H.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
    if(!this->textures["3C"].loadFromFile("res/txrs/cards/3C.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
}

void StatePlaying::initDecks() {
    this->decks.push_back(new BaseDeck(&this->decks));
    this->decks[0]->addCard(new Card(3, 2, &this->textures["2C"]));
    this->decks[0]->addCard(new Card(2, 2, &this->textures["2H"]));
    this->decks.push_back(new PlayerDeck(&this->decks));
    this->decks[1]->addCard(new Card(3, 3, &this->textures["3C"]));
}

void StatePlaying::update(const double& dt) {
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

void StatePlaying::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    //this->deck->render(target);
    for(auto& it: this->decks) {
	it->render(target);
    }
}

void StatePlaying::updateInput(const double& dt) {
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	//this->player->move(dt, 0.f, -1.f);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//this->player->move(dt, 0.f, 1.f);
}

void StatePlaying::endState() {
    std::printf("Ending state\n");
}
