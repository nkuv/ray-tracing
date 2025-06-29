#pragma once
#include <SFML/Graphics.hpp>
#include "sphere.hpp"
#include "light.hpp"
#include "utils.hpp"

class Scene {
public:
    Scene();
    void update(float deltaTime);
    void render(sf::RenderWindow& window);
    void handleInput(const sf::Vector2i& mousePos, bool leftPressed, bool rightPressed, 
                     bool upPressed, bool downPressed);
    
    // Getter methods for renderer access
    const Sphere& getSphere() const;
    const Light& getLight() const;
    
private:
    Sphere sphere;
    Light light;
    float moveSpeed;
    float smoothness;
    sf::Vector2f targetPosition;
}; 