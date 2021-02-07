#include "EndGame.h"

EndGame::EndGame(sf::Font* font) {
    this->font = font;
    this->initButtons();
    this->initBackground();
    this->text.setFont(*this->font);
    this->text.setFillColor(sf::Color::Green);
    this->text.setCharacterSize(30);
    this->text.setPosition(600.f, 200.f);
}

EndGame::~EndGame() {
    for(auto& it: this->buttons) 
	delete it.second;
}

void EndGame::initButtons() {
    //this->buttons.push_back(new Button(640.f, 360.f, 30, 30,
    //				this->font, "EXIT", 30, 
    //				sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
    //				sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)));
}

void EndGame::addButton(
    const std::string& key,
    const float& y,
    const float& width,
    const float& height,
    const unsigned& char_sz,
    const std::string& text) {

    float x = this->shape.getPosition().x + this->shape.getSize().x / 2.f - width / 2.f;

    this->buttons[key] = new Button(
    	x, y, width, height,
    	this->font, text, char_sz,
    	sf::Color(70, 70, 70, 200), sf::Color(250, 250, 250, 250), sf::Color(20, 20, 20, 50),
    	sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

void EndGame::initBackground() {
    this->shape.setSize(sf::Vector2f(1280.f, 720.f));
    this->shape.setFillColor(sf::Color(30, 30, 30, 100));
}

void EndGame::setText(const std::string& text) {
    this->text.setString(text);
}

void EndGame::update(const sf::Vector2f& mousePos) {
    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->update(mousePos);
    }
}

void EndGame::render(sf::RenderTarget* target) {
    if(!target) return;
    target->draw(this->shape);
    target->draw(this->text);
    for(auto& it: this->buttons) {
	if(it.second)
	    it.second->render(target);
    }
}
