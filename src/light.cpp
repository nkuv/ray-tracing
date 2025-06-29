#include "../include/light.hpp"

Light::Light(const sf::Vector2f& position, const sf::Color& color)
    : position(position), color(color) {}

void Light::setPosition(const sf::Vector2f& position) {
    this->position = position;
}

sf::Vector2f Light::getPosition() const {
    return position;
}

sf::Color Light::getColor() const {
    return color;
} 