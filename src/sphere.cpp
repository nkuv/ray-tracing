#include "../include/sphere.hpp"
#include <cmath>

Sphere::Sphere(const sf::Vector2f& position, float radius)
    : radius(radius), position(position), material(sf::Color::Red) {
}

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

float Sphere::getRadius() const {
    return radius;
}

RayHit Sphere::intersect(const Ray& ray) const {
    // Ray-sphere intersection using quadratic formula
    sf::Vector2f oc = ray.origin - position;
    
    float a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y;
    float b = 2.0f * (oc.x * ray.direction.x + oc.y * ray.direction.y);
    float c = oc.x * oc.x + oc.y * oc.y - radius * radius;
    
    float discriminant = b * b - 4 * a * c;
    
    if (discriminant < 0) {
        return RayHit(); // No intersection
    }
    
    float sqrtDisc = std::sqrt(discriminant);
    float t1 = (-b - sqrtDisc) / (2.0f * a);
    float t2 = (-b + sqrtDisc) / (2.0f * a);
    
    // Find the closest intersection point
    float t = (t1 > 0) ? t1 : t2;
    
    if (t <= 0 || t > ray.maxDistance) {
        return RayHit(); // No valid intersection
    }
    
    sf::Vector2f hitPoint = ray.getPointAtDistance(t);
    sf::Vector2f normal = getNormal(hitPoint);
    
    return RayHit(hitPoint, normal, t);
}

sf::Vector2f Sphere::getNormal(const sf::Vector2f& point) const {
    sf::Vector2f normal = point - position;
    float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
    if (length > 0) {
        normal = normal / length;
    }
    return normal;
}

sf::Color Sphere::getMaterial() const {
    return material;
}
