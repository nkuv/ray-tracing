#include<SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(1024,768),"Ray tracing");
    window.setFramerateLimit(0);

    float posX = 0.f;
    float posY = 0.f;
    float moveSpeed = 0.5f;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            } 
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  posX -= moveSpeed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  posX += moveSpeed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  posY -= moveSpeed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  posY += moveSpeed;
        
        window.clear(sf::Color::Green);

        sf::CircleShape sphere(100.f);
        sphere.setFillColor(sf::Color::Red);
        sphere.setPosition(
            posX,
            posY
        );
        window.draw(sphere);
        window.display();
    }

    return 0;
}