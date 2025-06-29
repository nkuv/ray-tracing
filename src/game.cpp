#include "../include/game.hpp"

Game::Game() 
    : window(sf::VideoMode(Utils::WINDOW_WIDTH, Utils::WINDOW_HEIGHT), "Ray Tracing")
    , isRunning(true) {
    window.setFramerateLimit(Utils::FRAME_RATE_LIMIT);
}

Game::~Game() {
    window.close();
}

void Game::run() {
    while (isRunning && window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        
        processEvents();
        update(deltaTime);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            isRunning = false;
        }
    }
}

void Game::update(float deltaTime) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    bool leftPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Left);
    bool rightPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Right);
    bool upPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
    bool downPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
    
    scene.handleInput(mousePos, leftPressed, rightPressed, upPressed, downPressed);
    scene.update(deltaTime);
}

void Game::render() {
    scene.render(window);
    window.display();
} 