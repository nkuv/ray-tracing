#include<SFML/Graphics.hpp>

int main(){
    sf::RenderWindow window(sf::VideoMode(1024,768),"Ray tracing");
    window.setFramerateLimit(60);

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            } 
        }
        window.clear(sf::Color::Green);

        sf::CircleShape sphere(100.f);
        sphere.setFillColor(sf::Color::Red);
        sphere.setPosition(
            (window.getSize().x - sphere.getRadius() * 2)/2,
            (window.getSize().y - sphere.getRadius() * 2)/2
        );
        window.draw(sphere);
        window.display();
    }

    return 0;
}