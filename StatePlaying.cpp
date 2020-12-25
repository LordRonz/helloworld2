#include "StatePlaying.h"

StatePlaying::StatePlaying(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states){
    this->initTextures();
    this->player = new Card(1, 1);
    this->player->createSprite(&this->textures["2C"]);
}

StatePlaying::~StatePlaying() {
    delete this->player;
}

void StatePlaying::initTextures() {
    this->textures["2C"].loadFromFile("res/txrs/cards/2C.png");
}

void StatePlaying::update(const double& dt) {
    //std::printf("Hello GameState\n");
    this->updateMousePos();
    this->updateInput(dt);
    //printf("%f %f\n", this->mousePosView.x, this->mousePosView.y);
    //if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	//std::printf("A\n");
}

void StatePlaying::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    this->player->render(target);
}

void StatePlaying::updateInput(const double& dt) {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	this->player->move(dt, 0.f, -1.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	this->player->move(dt, 0.f, 1.f);
}

void StatePlaying::endState() {
    std::printf("Ending state\n");
}
