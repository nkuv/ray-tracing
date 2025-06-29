#include "../include/raytracer.hpp"
#include "../include/scene.hpp"
#include <cmath>
#include <algorithm>

RayTracer::RayTracer() 
    : maxDepth(3)
    , shadowRays(8)
    , antiAliasing(false)
    , ambientIntensity(0.2f)
    , diffuseIntensity(0.8f)
    , specularIntensity(0.3f) {
}

void RayTracer::renderScene(sf::RenderWindow& window, const Scene& scene) {
    // Create render texture for pixel-perfect ray tracing
    sf::RenderTexture renderTexture;
    renderTexture.create(Utils::WINDOW_WIDTH, Utils::WINDOW_HEIGHT);
    renderTexture.clear(sf::Color::Black);
    
    const Light& light = scene.getLight();
    const Sphere& sphere = scene.getSphere();
    
    // Camera position (top-left of screen)
    sf::Vector2f cameraPos(0, 0);
    
    // Ray trace each pixel
    const int pixelStep = antiAliasing ? 1 : 2; // Anti-aliasing uses every pixel
    
    for (int x = 0; x < Utils::WINDOW_WIDTH; x += pixelStep) {
        for (int y = 0; y < Utils::WINDOW_HEIGHT; y += pixelStep) {
            sf::Vector2f pixelPos(static_cast<float>(x), static_cast<float>(y));
            
            // Create ray from camera to pixel
            sf::Vector2f rayDir = pixelPos - cameraPos;
            Ray ray(cameraPos, rayDir);
            
            // Trace the ray
            sf::Color pixelColor = traceRay(ray, scene);
            
            // Draw pixel
            sf::RectangleShape pixel(sf::Vector2f(pixelStep, pixelStep));
            pixel.setPosition(pixelPos);
            pixel.setFillColor(pixelColor);
            renderTexture.draw(pixel);
        }
    }
    
    renderTexture.display();
    
    // Draw the rendered texture
    sf::Sprite renderSprite(renderTexture.getTexture());
    window.draw(renderSprite);
    
    // Draw UI elements
    renderLight(window, light);
    renderSphereOutline(window, sphere);
}

sf::Color RayTracer::traceRay(const Ray& ray, const Scene& scene, int depth) {
    if (depth >= maxDepth) {
        return sf::Color::Black; // Max depth reached
    }
    
    // Find closest intersection
    RayHit hit = findClosestHit(ray, scene);
    
    if (!hit.hit) {
        return sf::Color(20, 20, 40); // Background color
    }
    
    // Calculate lighting at intersection point
    sf::Color lighting = calculateLighting(hit.point, hit.normal, scene);
    
    // Get material color
    const Sphere& sphere = scene.getSphere();
    sf::Color material = sphere.getMaterial();
    
    // Combine material and lighting
    sf::Color finalColor;
    finalColor.r = static_cast<uint8_t>(material.r * lighting.r / 255);
    finalColor.g = static_cast<uint8_t>(material.g * lighting.g / 255);
    finalColor.b = static_cast<uint8_t>(material.b * lighting.b / 255);
    
    return finalColor;
}

sf::Color RayTracer::calculateLighting(const sf::Vector2f& point, const sf::Vector2f& normal, const Scene& scene) {
    const Light& light = scene.getLight();
    
    // Ambient lighting
    sf::Color ambient = sf::Color(
        static_cast<uint8_t>(255 * ambientIntensity),
        static_cast<uint8_t>(255 * ambientIntensity),
        static_cast<uint8_t>(255 * ambientIntensity)
    );
    
    // Check if point is in shadow
    if (isInShadow(point, light, scene)) {
        return ambient; // Only ambient light in shadow
    }
    
    // Calculate diffuse lighting
    sf::Vector2f lightDir = light.getPosition() - point;
    float distance = Utils::calculateDistance(point, light.getPosition());
    float attenuation = 1.0f / (1.0f + 0.01f * distance + 0.001f * distance * distance);
    
    // Normalize light direction
    float lightLength = std::sqrt(lightDir.x * lightDir.x + lightDir.y * lightDir.y);
    if (lightLength > 0) {
        lightDir = lightDir / lightLength;
    }
    
    // Calculate diffuse intensity
    float diffuseDot = normal.x * lightDir.x + normal.y * lightDir.y;
    diffuseDot = std::max(0.0f, diffuseDot);
    
    sf::Color diffuse = sf::Color(
        static_cast<uint8_t>(255 * diffuseIntensity * diffuseDot * attenuation),
        static_cast<uint8_t>(255 * diffuseIntensity * diffuseDot * attenuation),
        static_cast<uint8_t>(255 * diffuseIntensity * diffuseDot * attenuation)
    );
    
    // Combine ambient and diffuse
    sf::Color finalLighting;
    finalLighting.r = std::min(255, ambient.r + diffuse.r);
    finalLighting.g = std::min(255, ambient.g + diffuse.g);
    finalLighting.b = std::min(255, ambient.b + diffuse.b);
    
    return finalLighting;
}

bool RayTracer::isInShadow(const sf::Vector2f& point, const Light& light, const Scene& scene) {
    sf::Vector2f lightDir = light.getPosition() - point;
    float distance = Utils::calculateDistance(point, light.getPosition());
    
    // Create shadow ray
    Ray shadowRay(point, lightDir, distance);
    
    // Check for intersections between point and light
    RayHit hit = findClosestHit(shadowRay, scene);
    
    // If we hit something before reaching the light, we're in shadow
    return hit.hit && hit.distance < distance;
}

RayHit RayTracer::findClosestHit(const Ray& ray, const Scene& scene) {
    const Sphere& sphere = scene.getSphere();
    return sphere.intersect(ray);
}

std::vector<Ray> RayTracer::generateRaysFromLight(const Light& light, int numRays) {
    std::vector<Ray> rays;
    float angleStep = 2.0f * M_PI / numRays;
    
    for (int i = 0; i < numRays; ++i) {
        float angle = i * angleStep;
        sf::Vector2f direction(std::cos(angle), std::sin(angle));
        rays.emplace_back(light.getPosition(), direction);
    }
    
    return rays;
}

std::vector<Ray> RayTracer::generateRaysFromCamera(const sf::Vector2f& cameraPos, int numRays) {
    std::vector<Ray> rays;
    float angleStep = 2.0f * M_PI / numRays;
    
    for (int i = 0; i < numRays; ++i) {
        float angle = i * angleStep;
        sf::Vector2f direction(std::cos(angle), std::sin(angle));
        rays.emplace_back(cameraPos, direction);
    }
    
    return rays;
}

void RayTracer::setMaxDepth(int depth) {
    maxDepth = depth;
}

void RayTracer::setShadowRays(int rays) {
    shadowRays = rays;
}

void RayTracer::setAntiAliasing(bool enabled) {
    antiAliasing = enabled;
}

void RayTracer::renderLight(sf::RenderWindow& window, const Light& light) {
    sf::CircleShape lightShape(Utils::LIGHT_RADIUS);
    lightShape.setOrigin(Utils::LIGHT_RADIUS, Utils::LIGHT_RADIUS);
    lightShape.setFillColor(light.getColor());
    lightShape.setPosition(light.getPosition());
    window.draw(lightShape);
}

void RayTracer::renderSphereOutline(sf::RenderWindow& window, const Sphere& sphere) {
    sf::CircleShape sphereOutline(sphere.getRadius());
    sphereOutline.setOrigin(sphere.getRadius(), sphere.getRadius());
    sphereOutline.setPosition(sphere.getPosition());
    sphereOutline.setFillColor(sf::Color::Transparent);
    sphereOutline.setOutlineColor(sf::Color::White);
    sphereOutline.setOutlineThickness(1.0f);
    window.draw(sphereOutline);
} 