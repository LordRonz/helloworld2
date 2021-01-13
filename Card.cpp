#include "Card.h"

Card::Card(const unsigned short& kind, const unsigned short& val, sf::Texture* texture, sf::Texture* buttText) : kind(kind), val(val) {
    // init
    this->createSprite(texture, buttText);
}

//bersih-bersih
Card::~Card() {
    delete this->sprite;
    delete this->buttSprite;
}

// dari texture depan dan belakang yang di pass, bikin spritenya
void Card::createSprite(sf::Texture* texture, sf::Texture* buttText) {
    this->sprite = new sf::Sprite;
    if(texture)
	this->sprite->setTexture(*texture);
    this->sprite->setScale(.6f, .6f);
    this->sprite->setColor(sf::Color(255, 255, 255, 230));

    this->buttSprite = new sf::Sprite;
    if(buttText)
	this->buttSprite->setTexture(*buttText);
    this->buttSprite->setScale(.6f, .6f);
}

//self explanatory
void Card::setPosition(const float& x, const float& y) {
   if(this->sprite)
	this->sprite->setPosition(x, y);
}

// bergoyang
void Card::move(const double& dt, const float& dir_x, const float& dir_y) {
    // maff stuff
    sf::Vector2f dir = sf::Vector2f(dir_x - this->sprite->getPosition().x, dir_y - this->sprite->getPosition().y);
    sf::Vector2f dirNorm = dir / static_cast<float>(std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2)));
    this->sprite->move(dirNorm * movSpeed);
    this->buttSprite->move(dirNorm * movSpeed);
}

//update, isinya cuma update input sih
void Card::update(const double& dt, const sf::Vector2f& mousePos) {
    this->updateInput(dt, mousePos);
}

// update input
void Card::updateInput(const double& dt, const sf::Vector2f& mousePos) {
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

// render
void Card::render(sf::RenderTarget* target) {
    if(!target) return;
    if(this->sprite && this->buttSprite)
        target->draw(this->butt ? *this->buttSprite : *this->sprite);
}

//self explanatory
const sf::Vector2f& Card::getPosition() const {
    return this->sprite->getPosition();
}

// bolak balikin spritenya pack
// inget, xor itu ngefilp bit nya
void Card::flip() {
    this->butt ^= 1;
}

// apakah saya sedang di klik??, yang ngatur ada di updateInput
const bool& Card::isClicked() const {
    return this->clicked;
}

//jenis apakah aku
const unsigned short& Card::getKind() const {
    return this->kind;
}

// nilaiku berapa sih, moga aja ACE
const unsigned short& Card::getVal() const {
    return this->val;
}
