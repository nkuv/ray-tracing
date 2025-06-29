#pragma once
#include <SFML/Graphics.hpp>
#include "sphere.hpp"
#include "light.hpp"
#include "utils.hpp"
#include "raytracer.hpp"

class Scene;

enum class RayDisplayMode {
    NONE,
    SPHERE_ONLY,
    ALL_RAYS,
    BOTH
};

class Renderer {
public:
    Renderer();
    
    void renderScene(sf::RenderWindow& window, const Scene& scene);
    void renderSphere(sf::RenderWindow& window, const Sphere& sphere, const Light& light);
    void renderLight(sf::RenderWindow& window, const Light& light);
    void render2DScene(sf::RenderWindow& window, const Scene& scene);
    void renderRealRayTracing(sf::RenderWindow& window, const Scene& scene);
    
    float calculateLighting(const sf::Vector2f& point, const Light& light);
    sf::Color calculateSphereColor(const Sphere& sphere, const Light& light);
    bool isPointInShadow(const sf::Vector2f& point, const Light& light, const Sphere& sphere);
    sf::Color calculate2DLighting(const sf::Vector2f& point, const Light& light, const Sphere& sphere);
    
    void clearWindow(sf::RenderWindow& window);
    void drawDebugInfo(sf::RenderWindow& window, const sf::Vector2f& mousePos, const Light& light);
    void drawRays(sf::RenderWindow& window, const Light& light, const Sphere& sphere);
    void drawAllRays(sf::RenderWindow& window, const Light& light);
    void drawLightRays(sf::RenderWindow& window, const Light& light, const sf::Vector2f& target, const sf::Color& color);
    void drawLightRadius(sf::RenderWindow& window, const Light& light);
    
    void toggleDebugMode();
    bool isDebugMode() const;
    void setRayDisplayMode(RayDisplayMode mode);
    RayDisplayMode getRayDisplayMode() const;
    void cycleRayDisplayMode();
    void toggle2DMode();
    bool is2DMode() const;
    void toggleRealRayTracing();
    bool isRealRayTracing() const;
    
private:
    float ambientLight;
    float diffuseIntensity;
    float maxLightDistance;
    bool showDebugInfo;
    bool is2DModeEnabled;
    bool isRealRayTracingEnabled;
    RayDisplayMode rayDisplayMode;
    RayTracer rayTracer;
}; 