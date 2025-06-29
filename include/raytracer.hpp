#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "ray.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include "utils.hpp"

class Scene;

class RayTracer {
public:
    RayTracer();
    
    void renderScene(sf::RenderWindow& window, const Scene& scene);
    sf::Color traceRay(const Ray& ray, const Scene& scene, int depth = 0);
    sf::Color calculateLighting(const sf::Vector2f& point, const sf::Vector2f& normal, const Scene& scene);
    bool isInShadow(const sf::Vector2f& point, const Light& light, const Scene& scene);
    RayHit findClosestHit(const Ray& ray, const Scene& scene);
    
    // Ray generation
    std::vector<Ray> generateRaysFromLight(const Light& light, int numRays);
    std::vector<Ray> generateRaysFromCamera(const sf::Vector2f& cameraPos, int numRays);
    
    // Settings
    void setMaxDepth(int depth);
    void setShadowRays(int rays);
    void setAntiAliasing(bool enabled);
    
private:
    void renderLight(sf::RenderWindow& window, const Light& light);
    void renderSphereOutline(sf::RenderWindow& window, const Sphere& sphere);
    
    int maxDepth;
    int shadowRays;
    bool antiAliasing;
    float ambientIntensity;
    float diffuseIntensity;
    float specularIntensity;
}; 