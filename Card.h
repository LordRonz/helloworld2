#pragma once

#include <stack>
#include <vector>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cmath>

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum Suit { Diamonds = 1, Hearts, Clubs, Spades };

class Card {
protected:
    unsigned short kind;
    unsigned short val;
    double movSpeed{10.f};
    sf::Vector2f currVelocity{0.f, 0.f};
    sf::Sprite* sprite{};
    bool hover{};

public:
    Card(unsigned short kind, unsigned short val, sf::Texture* texture);
    virtual ~Card();

    void createSprite(sf::Texture* texture);
    virtual void setPosition(const float x, const float y);
    virtual void move(const double& dt, const float x, const float y);
    virtual void update(const double& dt, const sf::Vector2f mousePos);
    virtual void render(sf::RenderTarget* target);
    unsigned short getKind();
    unsigned short getVal();
};
