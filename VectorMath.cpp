#include "VectorMath.h"

float VectorMath::vectorDistance(const float& x1, const float& y1, const float& x2, const float& y2) {
    const float dx = x2 - x1;
    const float dy = y2 - y1;

    return std::sqrt(std::pow(dx, 2) + std::pow(dy, 2));
}

float VectorMath::vectorDistance(const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
    const sf::Vector2f dVec = vec2 - vec1;

    return std::sqrt(std::pow(dVec.x, 2) + std::pow(dVec.y, 2));
}

sf::Vector2f VectorMath::normalizeDir(const float& x1, const float& y1, const float& x2, const float& y2) {
    const sf::Vector2f dir = sf::Vector2f(x1 - x2, y1 - y2);
    return dir / static_cast<float>(std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2)));
}

sf::Vector2f VectorMath::normalizeDir(const sf::Vector2f& vec1, const sf::Vector2f& vec2) {
    const sf::Vector2f dir = vec2 - vec1;
    return dir / static_cast<float>(std::sqrt(std::pow(dir.x, 2) + std::pow(dir.y, 2)));
}
