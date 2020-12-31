#include "VectorMath.h"

const float vectorDistance(const float& x1, const float& y1, const float& x2, const float& y2)
{
    const float dx = x2 - x1;
    const float dy = y2 - y1;

    return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

const float vectorDistance(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
{
    const sf::Vector2f dVec = vec2 - vec1;

    return std::sqrt(std::pow(dVec.x, 2) + std::pow(dVec.y, 2));
}
