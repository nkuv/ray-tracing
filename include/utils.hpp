#pragma once
#include <SFML/Graphics.hpp>

namespace Utils {
    constexpr int WINDOW_WIDTH = 1280;
    constexpr int WINDOW_HEIGHT = 720;
    constexpr int FRAME_RATE_LIMIT = 120;
    
    constexpr float DEFAULT_MOVE_SPEED = 5.0f;
    constexpr float DEFAULT_SMOOTHNESS = 0.1f;
    constexpr float LIGHT_RADIUS = 30.0f;
    constexpr float SPHERE_RADIUS = 100.0f;
    
    const sf::Color BACKGROUND_COLOR = sf::Color::Black;
    const sf::Color LIGHT_COLOR = sf::Color(255, 255, 200);
    
    float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2);
    float clamp(float value, float min, float max);
} 