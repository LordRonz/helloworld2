#pragma once

#include "SFML/System.hpp"
#include <cmath>
namespace VectorMath {
    float vectorDistance(const float& x1, const float& y1, const float& x2, const float& y2);

    float vectorDistance(const sf::Vector2f& vec1, const sf::Vector2f& vec2);

    sf::Vector2f normalizeDir(const float& x1, const float& y1, const float& x2, const float& y2);

    sf::Vector2f normalizeDir(const sf::Vector2f& vec1, const sf::Vector2f& vec2);
}
