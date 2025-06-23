#include<SFML/Graphics.hpp>
#include<cmath>

int main(){
    sf::RenderWindow window(sf::VideoMode(1280,720),"Ray tracing");
    window.setFramerateLimit(120);

    float posX = 0.f;
    float posY = 0.f;
    float moveSpeed = 5.f;
    float lightPosX = 400.f;
    float lightPosY = 300.f;
    float smoothness = 0.1f;

    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type==sf::Event::Closed){
                window.close();
            } 
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        posX += (mousePos.x - posX - 100.f) * smoothness;
        posY += (mousePos.y - posY - 100.f) * smoothness;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  posX -= moveSpeed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  posX += moveSpeed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  posY -= moveSpeed;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  posY += moveSpeed;
        
        window.clear(sf::Color::Black);

        float dx = lightPosX - posX;
        float dy = lightPosY - posY;
        float distance = std::sqrt(dx * dx + dy * dy);
        uint8_t brightness = static_cast<uint8_t>(255.f - (650.f-distance)/650.f);
        brightness = std::max(std::min(brightness, (uint8_t)255), (uint8_t)20);

        sf::CircleShape sphere(100.f);
        sphere.setFillColor(sf::Color(brightness,0,0));
        sphere.setPosition(posX,posY);
        window.draw(sphere);

        sf::CircleShape light(20.f);
        light.setFillColor(sf::Color::Yellow);
        light.setPosition(lightPosX,lightPosY);
        window.draw(light);

        window.display();
    }

    return 0;
}