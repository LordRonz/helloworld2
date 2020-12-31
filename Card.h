#pragma once

#include "stdafx.h"

#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

enum Suit { Diamonds = 1, Hearts, Clubs, Spades };

class Card {
protected:
    unsigned short kind;
    unsigned short val;
    float movSpeed{25.f};
    sf::Vector2f currVelocity{0.f, 0.f};
    sf::Sprite* sprite{};
    sf::Sprite* buttSprite{};
    bool hover{};
    bool selected{};
    bool wasSelected{};
    bool clicked{};
    bool butt{true};

public:
    Card(const unsigned short& kind, const unsigned short& val, sf::Texture* texture, sf::Texture* buttText);
    ~Card();

    void createSprite(sf::Texture* texture, sf::Texture* buttText);
    void setPosition(const float& x, const float& y);
    void move(const double& dt, const float& dir_x, const float& dir_y);
    void update(const double& dt, const sf::Vector2f& mousePos);
    void render(sf::RenderTarget* target);
    const sf::Vector2f& getPosition() const;
    const unsigned short& getKind() const;
    const unsigned short& getVal() const;
    void flip();
    const bool& isClicked() const;
};
