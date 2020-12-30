#include "Card.h"

Card::Card(const unsigned short& kind, const unsigned short& val, sf::Texture* texture, sf::Texture* buttText) {
    this->kind = kind;
    this->val = val;
    this->createSprite(texture, buttText);
    //this->sprite = new sf::Sprite;
    //this->sprite->setTexture(*texture);
}

Card::~Card() {
    delete this->sprite;
    delete this->buttSprite;
}

void Card::createSprite(sf::Texture* texture, sf::Texture* buttText) {
    this->sprite = new sf::Sprite;
    this->sprite->setTexture(*texture);
    this->sprite->setScale(.6f, .6f);
    this->buttSprite = new sf::Sprite;
    this->buttSprite->setTexture(*buttText);
    this->buttSprite->setScale(.6f, .6f);
    //this->sprite->setPosition(sf::Vector2f(10, 10));
    this->sprite->setColor(sf::Color(255, 255, 255, 230));
}

void Card::setPosition(const float& x, const float& y) {
   if(this->sprite)
	this->sprite->setPosition(x, y);
}

void Card::move(const double& dt, const float& dir_x, const float& dir_y) {
    //if(this->sprite)
    //	this->sprite->move(100 * dir_x * dt, 100 * dir_y * dt);
    sf::Vector2f dir = sf::Vector2f(dir_x - this->sprite->getPosition().x, dir_y - this->sprite->getPosition().y);
    sf::Vector2f dirNorm = dir / static_cast<float>(std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2)));
    this->sprite->move(dirNorm * movSpeed);
    this->buttSprite->move(dirNorm * movSpeed);
}

void Card::update(const double& dt, const sf::Vector2f& mousePos) {
    if(this->sprite->getGlobalBounds().contains(mousePos)) {
	if(!this->hover) {
	    this->sprite->setColor(sf::Color(255, 255, 255, 255));
	    this->hover = true;
	}
	this->selected = sf::Mouse::isButtonPressed(sf::Mouse::Left);
    }
    else {
	if(this->hover) {
	    this->sprite->setColor(sf::Color(255, 255, 255, 230));
	    this->hover = false;
	}
    }
    this->clicked = !this->selected && this->wasSelected;
    this->wasSelected = this->selected;
}

void Card::render(sf::RenderTarget* target) {
    if(this->sprite && this->buttSprite)
	target->draw(this->butt ? *this->buttSprite : *this->sprite);
}

const sf::Vector2f Card::getPosition() {
    return this->sprite->getPosition();
}

void Card::flip() {
    butt = !butt;
}

const bool Card::isClicked() {
    return this->clicked;
}

unsigned short Card::getKind() {
    return this->kind;
}

unsigned short Card::getVal() {
    return this->val;
}
