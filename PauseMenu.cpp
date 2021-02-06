#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Window* window, sf::Font* font) :font(font) {
    this->bg.setSize(
    	sf::Vector2f(
	   static_cast<float>(window->getSize().x), 
	   static_cast<float>(window->getSize().y)
    	)
    );
    this->bg.setFillColor(sf::Color(20, 20, 20, 100)); 
}

PauseMenu::~PauseMenu() {
    for(auto& it: this->buttons)
	delete it.second;
}

bool PauseMenu::isButtonPressed(const std::string& key) {
    return this->buttons[key] ? this->buttons[key]->isPressed() : false;
}

void PauseMenu::addButton(
    const std::string& key,
    const float& y,
    const float& width,
    const float& height,
    const unsigned& char_sz,
    const std::string& text) {
    
    float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new Button(
    	x, y, width, height,
    	this->font, text, char_sz,
    	sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
    	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);    
}

void PauseMenu::update(const sf::Vector2f& mousePosView) {
    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->update(mousePosView);
    }
}

void PauseMenu::render(sf::RenderTarget* target) {
    if(!target) return;
    target->draw(this->bg);
    target->draw(this->container);

    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->render(target);
    }
    target->draw(this->text);
}
