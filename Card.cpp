#include "Card.h"

Card::Card(unsigned short kind, unsigned short val, sf::Texture* texture) {
    this->kind = kind;
    this->val = val;
    this->createSprite(texture);
    //this->sprite = new sf::Sprite;
    //this->sprite->setTexture(*texture);
}

Card::~Card() {
    delete this->sprite;
}

void Card::createSprite(sf::Texture* texture) {
    this->sprite = new sf::Sprite;
    this->sprite->setTexture(*texture);
    this->sprite->setScale(.75f, .75f);
    //this->sprite->setPosition(sf::Vector2f(10, 10));
    this->sprite->setColor(sf::Color(255, 255, 255, 230));
}

void Card::setPosition(const float x, const float y) {
   if(this->sprite)
	this->sprite->setPosition(x, y);
}

void Card::move(const double& dt, const float dir_x, const float dir_y) {
    if(this->sprite)
	this->sprite->move(100 * dir_x * dt, 100 * dir_y * dt);
}

void Card::update(const double& dt, const sf::Vector2f mousePos) {
    if(this->sprite->getGlobalBounds().contains(mousePos)) {
	if(!this->hover) {
	    this->sprite->setColor(sf::Color(255, 255, 255, 255));
	    this->hover = true;
	}
    }
    else {
	if(this->hover) {
	    this->sprite->setColor(sf::Color(255, 255, 255, 230));
	    this->hover = false;
	}
    }
}

void Card::render(sf::RenderTarget* target) {
    if(this->sprite)
	target->draw(*this->sprite);
}

unsigned short Card::getKind() {
    return this->kind;
}

unsigned short Card::getVal() {
    return this->val;
}
