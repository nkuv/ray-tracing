#include "../include/renderer.hpp"
#include "../include/scene.hpp"
#include <cmath>

Renderer::Renderer() 
    : ambientLight(0.3f)
    , diffuseIntensity(2.0f)
    , maxLightDistance(800.0f)
    , showDebugInfo(true)
    , is2DModeEnabled(false)
    , isRealRayTracingEnabled(false)
    , rayDisplayMode(RayDisplayMode::ALL_RAYS) {
}

void Renderer::renderScene(sf::RenderWindow& window, const Scene& scene) {
    if (isRealRayTracingEnabled) {
        renderRealRayTracing(window, scene);
    } else if (is2DModeEnabled) {
        render2DScene(window, scene);
    } else {
        clearWindow(window);
        
        // Draw rays based on display mode
        if (showDebugInfo) {
            switch (rayDisplayMode) {
                case RayDisplayMode::NONE:
                    break;
                case RayDisplayMode::SPHERE_ONLY:
                    drawRays(window, scene.getLight(), scene.getSphere());
                    break;
                case RayDisplayMode::ALL_RAYS:
                    drawAllRays(window, scene.getLight());
                    break;
                case RayDisplayMode::BOTH:
                    drawAllRays(window, scene.getLight());
                    drawRays(window, scene.getLight(), scene.getSphere());
                    break;
            }
        }
        
        renderSphere(window, scene.getSphere(), scene.getLight());
        renderLight(window, scene.getLight());
    }
}

void Renderer::renderRealRayTracing(sf::RenderWindow& window, const Scene& scene) {
    rayTracer.renderScene(window, scene);
}

void Renderer::render2DScene(sf::RenderWindow& window, const Scene& scene) {
    const Light& light = scene.getLight();
    const Sphere& sphere = scene.getSphere();
    
    // Create a texture to render the 2D lighting
    sf::RenderTexture lightingTexture;
    lightingTexture.create(Utils::WINDOW_WIDTH, Utils::WINDOW_HEIGHT);
    lightingTexture.clear(sf::Color::Black);
    
    // Fill the screen with light, but create shadows where the sphere blocks it
    const int pixelStep = 2; // Reduced for better quality
    
    for (int x = 0; x < Utils::WINDOW_WIDTH; x += pixelStep) {
        for (int y = 0; y < Utils::WINDOW_HEIGHT; y += pixelStep) {
            sf::Vector2f pixelPos(static_cast<float>(x), static_cast<float>(y));
            
            // Calculate lighting for this pixel
            sf::Color pixelColor = calculate2DLighting(pixelPos, light, sphere);
            
            // Draw a small rectangle for this pixel
            sf::RectangleShape pixel(sf::Vector2f(pixelStep, pixelStep));
            pixel.setPosition(pixelPos);
            pixel.setFillColor(pixelColor);
            lightingTexture.draw(pixel);
        }
    }
    
    lightingTexture.display();
    
    // Draw the lighting texture to the window
    sf::Sprite lightingSprite(lightingTexture.getTexture());
    window.draw(lightingSprite);
    
    // Draw the sphere outline to show its position
    sf::CircleShape sphereOutline(sphere.getRadius());
    sphereOutline.setOrigin(sphere.getRadius(), sphere.getRadius());
    sphereOutline.setPosition(sphere.getPosition());
    sphereOutline.setFillColor(sf::Color::Transparent);
    sphereOutline.setOutlineColor(sf::Color::White);
    sphereOutline.setOutlineThickness(2.0f);
    window.draw(sphereOutline);
    
    // Draw the light source
    renderLight(window, light);
}

void Renderer::renderSphere(sf::RenderWindow& window, const Sphere& sphere, const Light& light) {
    sf::CircleShape circle(sphere.getRadius());
    circle.setOrigin(sphere.getRadius(), sphere.getRadius());
    circle.setPosition(sphere.getPosition());
    sf::Color sphereColor = calculateSphereColor(sphere, light);
    circle.setFillColor(sphereColor);
    
    window.draw(circle);
}

void Renderer::renderLight(sf::RenderWindow& window, const Light& light) {
    sf::CircleShape lightShape(Utils::LIGHT_RADIUS);
    lightShape.setOrigin(Utils::LIGHT_RADIUS, Utils::LIGHT_RADIUS);
    lightShape.setFillColor(light.getColor());
    lightShape.setPosition(light.getPosition());
    window.draw(lightShape);
}

float Renderer::calculateLighting(const sf::Vector2f& point, const Light& light) {
    float distance = Utils::calculateDistance(point, light.getPosition());
    
    float diffuse = Utils::clamp(1.0f - (distance / maxLightDistance), 0.0f, 1.0f);
    
    float totalLighting = ambientLight + (diffuseIntensity * diffuse);
    
    return Utils::clamp(totalLighting, 0.0f, 1.0f);
}

sf::Color Renderer::calculateSphereColor(const Sphere& sphere, const Light& light) {
    sf::Vector2f spherePos = sphere.getPosition();
    float lighting = calculateLighting(spherePos, light);
    uint8_t redValue = static_cast<uint8_t>(255 * lighting);
    
    return sf::Color(redValue, 0, 0);
}

bool Renderer::isPointInShadow(const sf::Vector2f& point, const Light& light, const Sphere& sphere) {
    // Check if the point is behind the sphere relative to the light
    sf::Vector2f lightToPoint = point - light.getPosition();
    sf::Vector2f lightToSphere = sphere.getPosition() - light.getPosition();
    
    // Calculate distances
    float distanceToPoint = Utils::calculateDistance(light.getPosition(), point);
    float distanceToSphere = Utils::calculateDistance(light.getPosition(), sphere.getPosition());
    
    // If point is closer to light than sphere, it's not in shadow
    if (distanceToPoint < distanceToSphere) {
        return false;
    }
    
    // Calculate the angle between light-to-point and light-to-sphere vectors
    float dotProduct = lightToPoint.x * lightToSphere.x + lightToPoint.y * lightToSphere.y;
    float pointMagnitude = std::sqrt(lightToPoint.x * lightToPoint.x + lightToPoint.y * lightToPoint.y);
    float sphereMagnitude = std::sqrt(lightToSphere.x * lightToSphere.x + lightToSphere.y * lightToSphere.y);
    
    if (pointMagnitude == 0 || sphereMagnitude == 0) {
        return false;
    }
    
    float cosAngle = dotProduct / (pointMagnitude * sphereMagnitude);
    cosAngle = Utils::clamp(cosAngle, -1.0f, 1.0f);
    float angle = std::acos(cosAngle);
    
    // Calculate the angle subtended by the sphere at the light
    float sphereAngle = std::asin(sphere.getRadius() / distanceToSphere);
    
    // If the angle is less than the sphere's subtended angle, the point is in shadow
    return angle < sphereAngle;
}

sf::Color Renderer::calculate2DLighting(const sf::Vector2f& point, const Light& light, const Sphere& sphere) {
    // Check if point is in shadow
    if (isPointInShadow(point, light, sphere)) {
        return sf::Color(10, 10, 10); // Very dark shadow
    }
    
    // Calculate lighting based on distance from light
    float distance = Utils::calculateDistance(point, light.getPosition());
    float lighting = Utils::clamp(1.0f - (distance / maxLightDistance), 0.0f, 1.0f);
    
    // Apply stronger lighting with ambient light
    lighting = ambientLight + (diffuseIntensity * lighting);
    lighting = Utils::clamp(lighting, 0.0f, 1.0f);
    
    // Create a bright, warm light color
    uint8_t intensity = static_cast<uint8_t>(255 * lighting);
    return sf::Color(
        intensity, 
        static_cast<uint8_t>(intensity * 0.9f), 
        static_cast<uint8_t>(intensity * 0.6f)
    );
}

void Renderer::clearWindow(sf::RenderWindow& window) {
    window.clear(Utils::BACKGROUND_COLOR);
}

void Renderer::drawDebugInfo(sf::RenderWindow& window, const sf::Vector2f& mousePos, const Light& light) {
    if (!showDebugInfo) return;
    
    // Draw thick ray from light to mouse
    sf::RectangleShape ray;
    ray.setSize(sf::Vector2f(Utils::calculateDistance(light.getPosition(), mousePos), 3.0f)); // Thick ray
    ray.setFillColor(sf::Color::Yellow);
    
    // Calculate rotation angle
    float angle = std::atan2(mousePos.y - light.getPosition().y, mousePos.x - light.getPosition().x);
    ray.setRotation(angle * 180.0f / M_PI);
    
    // Position the ray at the light center
    ray.setOrigin(0, 1.5f); // Center vertically
    ray.setPosition(light.getPosition());
    
    window.draw(ray);
}

void Renderer::drawAllRays(sf::RenderWindow& window, const Light& light) {
    const int numRays = 36; // More rays for better coverage
    float angleStep = 2.0f * M_PI / numRays;
    
    for (int i = 0; i < numRays; ++i) {
        float angle = i * angleStep;
        
        // Calculate ray end point at maximum light distance
        sf::Vector2f rayEnd = light.getPosition() + sf::Vector2f(
            std::cos(angle) * maxLightDistance,
            std::sin(angle) * maxLightDistance
        );
        
        // Calculate lighting intensity at this point
        float lighting = calculateLighting(rayEnd, light);
        
        // Create color based on lighting intensity
        sf::Color rayColor = sf::Color(
            static_cast<uint8_t>(255 * lighting * 0.5f), // Red component
            static_cast<uint8_t>(255 * lighting * 0.4f), // Green component
            0,                                           // Blue component
            static_cast<uint8_t>(50 + 150 * lighting)    // Alpha (transparency)
        );
        
        drawLightRays(window, light, rayEnd, rayColor);
    }
}

void Renderer::drawRays(sf::RenderWindow& window, const Light& light, const Sphere& sphere) {
    // Draw main ray from light to sphere center
    drawLightRays(window, light, sphere.getPosition(), sf::Color(255, 255, 0, 150));
    
    // Draw multiple rays around the sphere to show the lighting effect
    const int numRays = 12;
    float angleStep = 2.0f * M_PI / numRays;
    
    for (int i = 0; i < numRays; ++i) {
        float angle = i * angleStep;
        sf::Vector2f rayEnd = sphere.getPosition() + sf::Vector2f(
            std::cos(angle) * sphere.getRadius(),
            std::sin(angle) * sphere.getRadius()
        );
        
        // Calculate lighting intensity for this ray
        float lighting = calculateLighting(rayEnd, light);
        sf::Color rayColor = sf::Color(
            static_cast<uint8_t>(255 * lighting),
            static_cast<uint8_t>(255 * lighting * 0.5f),
            0,
            static_cast<uint8_t>(100 + 155 * lighting)
        );
        
        drawLightRays(window, light, rayEnd, rayColor);
    }
    
    // Draw light radius indicator
    drawLightRadius(window, light);
}

void Renderer::drawLightRays(sf::RenderWindow& window, const Light& light, const sf::Vector2f& target, const sf::Color& color) {
    // Calculate ray properties
    float distance = Utils::calculateDistance(light.getPosition(), target);
    float angle = std::atan2(target.y - light.getPosition().y, target.x - light.getPosition().x);
    
    // Create thick ray using RectangleShape
    sf::RectangleShape ray;
    ray.setSize(sf::Vector2f(distance, 2.0f)); // Thick ray (2 pixels wide)
    ray.setFillColor(color);
    ray.setRotation(angle * 180.0f / M_PI);
    
    // Position the ray at the light center
    ray.setOrigin(0, 1.0f); // Center vertically
    ray.setPosition(light.getPosition());
    
    window.draw(ray);
}

void Renderer::drawLightRadius(sf::RenderWindow& window, const Light& light) {
    // Draw a circle showing the maximum light distance
    sf::CircleShape lightRadius(maxLightDistance);
    lightRadius.setOrigin(maxLightDistance, maxLightDistance);
    lightRadius.setPosition(light.getPosition());
    lightRadius.setFillColor(sf::Color::Transparent);
    lightRadius.setOutlineColor(sf::Color(255, 255, 0, 50));
    lightRadius.setOutlineThickness(1.0f);
    
    window.draw(lightRadius);
}

void Renderer::toggleDebugMode() {
    showDebugInfo = !showDebugInfo;
}

bool Renderer::isDebugMode() const {
    return showDebugInfo;
}

void Renderer::setRayDisplayMode(RayDisplayMode mode) {
    rayDisplayMode = mode;
}

RayDisplayMode Renderer::getRayDisplayMode() const {
    return rayDisplayMode;
}

void Renderer::cycleRayDisplayMode() {
    switch (rayDisplayMode) {
        case RayDisplayMode::NONE:
            rayDisplayMode = RayDisplayMode::SPHERE_ONLY;
            break;
        case RayDisplayMode::SPHERE_ONLY:
            rayDisplayMode = RayDisplayMode::ALL_RAYS;
            break;
        case RayDisplayMode::ALL_RAYS:
            rayDisplayMode = RayDisplayMode::BOTH;
            break;
        case RayDisplayMode::BOTH:
            rayDisplayMode = RayDisplayMode::NONE;
            break;
    }
}

void Renderer::toggle2DMode() {
    is2DModeEnabled = !is2DModeEnabled;
    if (is2DModeEnabled) {
        isRealRayTracingEnabled = false;
    }
}

bool Renderer::is2DMode() const {
    return is2DModeEnabled;
}

void Renderer::toggleRealRayTracing() {
    isRealRayTracingEnabled = !isRealRayTracingEnabled;
    if (isRealRayTracingEnabled) {
        is2DModeEnabled = false;
    }
}

bool Renderer::isRealRayTracing() const {
    return isRealRayTracingEnabled;
} 