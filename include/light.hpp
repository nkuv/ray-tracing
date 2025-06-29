#pragma once
#include <SFML/Graphics.hpp>

class Light {
public:
    explicit Light(const sf::Vector2f& position, const sf::Color& color);
    void setPosition(const sf::Vector2f& position);
    sf::Vector2f getPosition() const;
    sf::Color getColor() const;
private:
    sf::Vector2f position;
    sf::Color color;
}; 