#pragma once
#include <SFML/Graphics.hpp>
#include "utils.hpp"
#include "ray.hpp"

class Sphere {
public:
    Sphere(const sf::Vector2f& position, float radius);
    void draw(sf::RenderWindow& window, sf::Vector2f lightPos);
    sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& position);
    float getRadius() const;
    
    // Ray tracing methods
    RayHit intersect(const Ray& ray) const;
    sf::Vector2f getNormal(const sf::Vector2f& point) const;
    sf::Color getMaterial() const;
    
private:
    float radius;
    sf::Vector2f position;
    sf::Color material; // Material properties for ray tracing
};
