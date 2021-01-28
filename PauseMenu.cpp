#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::Window* window, sf::Font* font) :font(font) {
    
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
    
}

void PauseMenu::update(const sf::Vector2f& mousePosWindow) {
    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->update(mousePosWindow);
    }
}

void PauseMenu::render(sf::RenderTarget* target) {
    if(!target) return;
    target->draw(this->bg);

    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->render(target);
    }
    target->draw(this->text);
}
