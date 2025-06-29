#include "../include/sphere.hpp"
#include <cmath>

Sphere::Sphere(const sf::Vector2f& position, float radius)
    : radius(radius), position(position) {}

void Sphere::draw(sf::RenderWindow& window, sf::Vector2f lightPos) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(position);

    float dist = Utils::calculateDistance(position, lightPos);
    float intensity = Utils::clamp(1.f - dist / 300.f, 0.f, 1.f);
    circle.setFillColor(sf::Color(255 * intensity, 0, 0));
    
    window.draw(circle);
}

sf::Vector2f Sphere::getPosition() const {
    return position;
}

void Sphere::setPosition(const sf::Vector2f& newPosition) {
    position = newPosition;
}
