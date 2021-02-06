#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) {
    this->window = window;
    this->states = states;
    this->initKeyTimer();
}

State::~State() {

}

void State::initKeyTimer() {
    this->keyTimeMax = 0.2;
    this->keyTimer.restart();
}

bool State::getKeyTime() {
    if(this->keyTimer.getElapsedTime().asSeconds() > this->keyTimeMax) {
	this->keyTimer.restart();
	return 1;
    }
    return 0;
}

void State::pauseState() {
    this->paused = 1;
}

void State::unpauseState() {
    this->paused = 0;
}

const bool& State::getEnd() const {
    return this->end;
}

void State::endState() {
    this->end = true;
}

void State::updateMousePos() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
