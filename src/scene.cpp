#include "../include/scene.hpp"

Scene::Scene() 
    : sphere(sf::Vector2f(0.f, 0.f), Utils::SPHERE_RADIUS)
    , light(sf::Vector2f(400.f, 300.f), Utils::LIGHT_COLOR)
    , moveSpeed(Utils::DEFAULT_MOVE_SPEED)
    , smoothness(Utils::DEFAULT_SMOOTHNESS)
    , targetPosition(0.f, 0.f) {
}

void Scene::update(float deltaTime) {
    // Update sphere position with smooth movement
    sf::Vector2f currentPos = sphere.getPosition();
    currentPos += (targetPosition - currentPos) * smoothness;
    sphere.setPosition(currentPos);
}

void Scene::render(sf::RenderWindow& window) {
    // Clear the window
    window.clear(Utils::BACKGROUND_COLOR);
    
    // Draw the sphere with lighting
    sphere.draw(window, light.getPosition());
    
    // Draw the light
    sf::CircleShape lightShape(Utils::LIGHT_RADIUS);
    lightShape.setFillColor(light.getColor());
    lightShape.setPosition(light.getPosition());
    window.draw(lightShape);
}

void Scene::handleInput(const sf::Vector2i& mousePos, bool leftPressed, bool rightPressed, 
                       bool upPressed, bool downPressed) {
    // Handle mouse input for sphere target position
    targetPosition = sf::Vector2f(mousePos.x - 100.f, mousePos.y - 100.f);
    
    // Handle keyboard input for light movement
    sf::Vector2f lightPos = light.getPosition();
    if (leftPressed) lightPos.x -= moveSpeed;
    if (rightPressed) lightPos.x += moveSpeed;
    if (upPressed) lightPos.y -= moveSpeed;
    if (downPressed) lightPos.y += moveSpeed;
    
    light.setPosition(lightPos);
} 