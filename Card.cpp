#include "Card.h"

Card::Card(unsigned short kind, unsigned short val) {
    this->kind = kind;
    this->val = val;
    //this->sprite = new sf::Sprite;
    //this->sprite->setTexture(*texture);
}

Card::~Card() {
    delete this->sprite;
}

void Card::createSprite(sf::Texture* texture) {
    this->texture = texture;
    this->sprite = new sf::Sprite;
    this->sprite->setTexture(*this->texture);
}

void Card::setPosition(const float x, const float y) {
   if(this->sprite)
	this->sprite->setPosition(x, y);
}

void Card::move(const double& dt, const float dir_x, const float dir_y) {
    if(this->sprite)
	this->sprite->move(100 * dir_x * dt, 100 * dir_y * dt);
}

void Card::update(const double& dt) {}

void Card::render(sf::RenderTarget* target) {
    if(this->sprite)
	target->draw(*this->sprite);
}
