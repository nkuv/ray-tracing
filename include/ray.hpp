#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Ray {
    sf::Vector2f origin;
    sf::Vector2f direction;
    float maxDistance;
    
    Ray(const sf::Vector2f& origin, const sf::Vector2f& direction, float maxDistance = 1000.0f);
    
    sf::Vector2f getPointAtDistance(float distance) const;
    void normalize();
};

struct RayHit {
    sf::Vector2f point;
    sf::Vector2f normal;
    float distance;
    bool hit;
    
    RayHit();
    RayHit(const sf::Vector2f& point, const sf::Vector2f& normal, float distance);
}; 