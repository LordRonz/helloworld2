#include "State.h"

State::State(sf::RenderWindow* window, std::stack<State*>* states) {
    this->window = window;
    this->states = states;
}

State::~State() {

}

const bool& State::getEnd() const {
    return this->end;
}

void State::checkEnd() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
	this->end = true;
    }
}

void State::updateMousePos() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
