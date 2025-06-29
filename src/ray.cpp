#include "../include/ray.hpp"
#include <cmath>

Ray::Ray(const sf::Vector2f& origin, const sf::Vector2f& direction, float maxDistance)
    : origin(origin), direction(direction), maxDistance(maxDistance) {
    normalize();
}

sf::Vector2f Ray::getPointAtDistance(float distance) const {
    return origin + direction * distance;
}

void Ray::normalize() {
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction = direction / length;
    }
}

RayHit::RayHit() : point(0, 0), normal(0, 0), distance(0), hit(false) {
}

RayHit::RayHit(const sf::Vector2f& point, const sf::Vector2f& normal, float distance)
    : point(point), normal(normal), distance(distance), hit(true) {
} 