#include "../include/utils.hpp"
#include <cmath>

namespace Utils {
    float calculateDistance(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
        float dx = pos2.x - pos1.x;
        float dy = pos2.y - pos1.y;
        return std::sqrt(dx * dx + dy * dy);
    }
    
    float clamp(float value, float min, float max) {
        if (value < min) return min;
        if (value > max) return max;
        return value;
    }
} 