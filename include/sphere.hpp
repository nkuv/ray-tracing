#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"

class Sphere {
public:
    Sphere(const sf::Vector2f& position, float radius);
    void draw(sf::RenderWindow& window, sf::Vector2f lightPos);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);

private:
    float radius;
    sf::Vector2f position;
};
