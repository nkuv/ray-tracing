#include <SFML/Graphics.hpp>
#include "../include/scene.hpp"
#include "../include/renderer.hpp"
#include "../include/utils.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(Utils::WINDOW_WIDTH, Utils::WINDOW_HEIGHT), "Ray Tracing");
    window.setFramerateLimit(Utils::FRAME_RATE_LIMIT);

    Scene scene;
    Renderer renderer;
    
    sf::Clock clock;
    bool rKeyPressed = false;
    bool tKeyPressed = false; 
    bool twoKeyPressed = false;
    bool threeKeyPressed = false;
    
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
        bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
        bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (!rKeyPressed) {
                renderer.toggleDebugMode();
                rKeyPressed = true;
            }
        } else {
            rKeyPressed = false;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
            if (!tKeyPressed) {
                renderer.cycleRayDisplayMode();
                tKeyPressed = true;
            }
        } else {
            tKeyPressed = false;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            if (!twoKeyPressed) {
                renderer.toggle2DMode();
                twoKeyPressed = true;
            }
        } else {
            twoKeyPressed = false;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            if (!threeKeyPressed) {
                renderer.toggleRealRayTracing();
                threeKeyPressed = true;
            }
        } else {
            threeKeyPressed = false;
        }
        
        scene.handleInput(mousePos, leftPressed, rightPressed, upPressed, downPressed);
        scene.update(deltaTime);
        
        renderer.renderScene(window, scene);
        window.display();
    }
    return 0;
}