#include "../include/scene.hpp"

Scene::Scene() 
    : sphere(sf::Vector2f(0.f, 0.f), Utils::SPHERE_RADIUS)
    , light(sf::Vector2f(400.f, 300.f), Utils::LIGHT_COLOR)
    , moveSpeed(Utils::DEFAULT_MOVE_SPEED)
    , smoothness(Utils::DEFAULT_SMOOTHNESS)
    , targetPosition(0.f, 0.f) {
}

void Scene::update(float deltaTime) {
    sf::Vector2f currentPos = sphere.getPosition();
    currentPos += (targetPosition - currentPos) * smoothness;
    sphere.setPosition(currentPos);
}

void Scene::render(sf::RenderWindow& window) {
    window.clear(Utils::BACKGROUND_COLOR);
    
    sphere.draw(window, light.getPosition());
    
    sf::CircleShape lightShape(Utils::LIGHT_RADIUS);
    lightShape.setFillColor(light.getColor());
    lightShape.setPosition(light.getPosition());
    window.draw(lightShape);
}

void Scene::handleInput(const sf::Vector2i& mousePos, bool leftPressed, bool rightPressed, 
                       bool upPressed, bool downPressed) {
    targetPosition = sf::Vector2f(mousePos.x, mousePos.y);
    
    sf::Vector2f lightPos = light.getPosition();
    if (leftPressed) lightPos.x -= moveSpeed;
    if (rightPressed) lightPos.x += moveSpeed;
    if (upPressed) lightPos.y -= moveSpeed;
    if (downPressed) lightPos.y += moveSpeed;
    
    light.setPosition(lightPos);
}

const Sphere& Scene::getSphere() const {
    return sphere;
}

const Light& Scene::getLight() const {
    return light;
} 