#include "Game.h"
#define SCRWIDTH 1280
#define SCRHEIGHT 720
#define FPS 60

Game::Game() {
    this->initWindow();
    this->initStates();
}

Game::~Game() {
    delete this->window;
    while(!this->states.empty()) {
	delete this->states.top();
	this->states.pop();
    }
}

void Game::endApplication() {
    std::puts("Ending Application!");
}

void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::updateEvents() {
    while(this->window->pollEvent(this->event)) {
	switch(this->event.type) {
	    case sf::Event::Closed:
		this->window->close();
		break;
	    default:
		break;
	}
    }
}

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(SCRWIDTH, SCRHEIGHT), "Hello World 2");
    this->window->setFramerateLimit(FPS);
    this->window->setVerticalSyncEnabled(false);
}

void Game::initStates() {
    this->states.push(new GameState(this->window, &this->states));
}

void Game::update() {
    this->updateDt();

    this->updateEvents();

    if(!this->states.empty()) {
	if(this->window->hasFocus()) {
	    this->states.top()->update(this->dt);
	    if(this->states.top()->getEnd()) {
		this->states.top()->endState();
		delete this->states.top();
		this->states.pop();
	    }
	}
    }

    else {
	this->window->close();
    }
}

void Game::render() {
    this->window->clear();

    if(!this->states.empty()) {
	this->states.top()->render();
    }

    this->window->display();
}

void Game::run() {
    while(this->window->isOpen()) {
	this->update();
	this->render();
    }
}
