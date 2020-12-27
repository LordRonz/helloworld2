#pragma once

#include <stack>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>
#include <cstdlib>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum Suit { Diamonds = 1, Hearts, Clubs, Spades };

class Card {
protected:
    unsigned short kind;
    unsigned short val;
    float movSpeed{10.f};
    sf::Vector2f currVelocity{0.f, 0.f};
    sf::Sprite* sprite{};
    sf::Sprite* buttSprite{};
    bool hover{};
    bool butt{true};

public:
    Card(unsigned short kind, unsigned short val, sf::Texture* texture, sf::Texture* buttText);
    virtual ~Card();

    void createSprite(sf::Texture* texture, sf::Texture* buttText);
    virtual void setPosition(const float x, const float y);
    virtual void move(const double& dt, const float dir_x, const float dir_y);
    virtual void update(const double& dt, const sf::Vector2f mousePos);
    virtual void render(sf::RenderTarget* target);
    virtual const sf::Vector2f getPosition();
    unsigned short getKind();
    virtual void flip();
    unsigned short getVal();
};
