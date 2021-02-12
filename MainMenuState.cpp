#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states) {
    
}

MainMenuState::~MainMenuState() {
    for(auto& it: buttons)
	delete it.second;
}

void MainMenuState::initFonts() {
    if(!this->font.loadFromFile("res/fonts/lhf_american_sans.ttf"))
	std::puts("ERROR LOADING FONT");
}

void MainMenuState::initGui() {
    this->bg.setSize(sf::Vector2f(this->window->getSize()));
    if (!this->bgTexture.loadFromFile("res/txrs/bg/bg2.png")) {
	std::puts("ERROR LOADING BG TEXTURE");
    }
    this->bg.setTexture(&this->bgTexture);
    
    this->btnBackground.setSize(
    	sf::Vector2f(
    		static_cast<float>(this->window->getSize().x / 5), 
    		static_cast<float>(this->window->getSize().y)
    	)
    );
    
    this->btnBackground.setPosition(std::floor(static_cast<float>(this->window->getSize().x) * (11.5 / 100.f)), 0.f);
    this->btnBackground.setFillColor(sf::Color(10, 10, 10, 220));
    
}
void MainMenuState::updateInput(const double& dt) {

}

void MainMenuState::updateButtons() {

}

void MainMenuState::update(const double& dt) {

}

void MainMenuState::renderButtons(sf::RenderTarget* target) {

}
void MainMenuState::render(sf::RenderTarget* target) {

}
