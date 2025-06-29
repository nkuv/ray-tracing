#pragma once
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "utils.hpp"

class Game {
public:
    Game();
    ~Game();
    
    void run();
    
private:
    void processEvents();
    void update(float deltaTime);
    void render();
    
    sf::RenderWindow window;
    Scene scene;
    sf::Clock clock;
    bool isRunning;
}; 