#include "StatePlaying.h"

StatePlaying::StatePlaying(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
    this->initTextures();
    this->initDecks();
}

StatePlaying::~StatePlaying() {
    //delete this->player;
    delete this->deck;
}

void StatePlaying::initTextures() {
    if(!this->textures["2C"].loadFromFile("res/txrs/cards/2C.png"))
	printf("ERROR LOADING CARD TEXTURE\n");
}

void StatePlaying::initDecks() {
    this->deck = new Deck();
    deck->addCard(new Card(1, 1, &this->textures["2C"]), "2C");
}

void StatePlaying::update(const double& dt) {
    //std::printf("Hello GameState\n");
    this->updateMousePos();
    this->updateInput(dt);
    this->deck->update(dt, this->mousePosView);
    //printf("%f %f\n", this->mousePosView.x, this->mousePosView.y);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//std::printf("A\n");
}

void StatePlaying::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    this->deck->render(target);
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
