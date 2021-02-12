#include "MainMenuState.h"

MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states) : State(window, states) {
   this->initFonts();
   this->initGui();
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

    this->buttons["GAME_STATE"] = new Button(
	std::floor(0.156f * this->window->getSize().x), std::floor(0.3f * this->window->getSize().y), 
	std::floor(0.13f * this->window->getSize().x), std::floor(0.06f * this->window->getSize().y),
	&this->font, "Play", (this->window->getSize().x + this->window->getSize().y) / 60,
	sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
    );
    this->buttons["EXIT_STATE"] = new Button(
	std::floor(0.156f * this->window->getSize().x), std::floor(0.65f * this->window->getSize().y), 
	std::floor(0.13f * this->window->getSize().x), std::floor(0.06f * this->window->getSize().y),
	&this->font, "Quit", (this->window->getSize().x + this->window->getSize().y) / 60,
	sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
	sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
    );

}
void MainMenuState::updateInput(const double& dt) {

}

void MainMenuState::updateButtons() {
    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->update(this->mousePosView);
    }

    if(this->buttons["GAME_STATE"]->isPressed()) {
	this->states->push(new GameState(this->window, this->states));
    }
    else if(this->buttons["EXIT_STATE"]->isPressed()) {
	this->endState();
    }
}

void MainMenuState::update(const double& dt) {
    this->updateMousePos();
    this->updateButtons();
}

void MainMenuState::renderButtons(sf::RenderTarget* target) {
    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->render(target);
    }
}
void MainMenuState::render(sf::RenderTarget* target) {
    if(!target) target = this->window;
    target->draw(this->bg);
    target->draw(this->btnBackground);
    this->renderButtons(target);
}
