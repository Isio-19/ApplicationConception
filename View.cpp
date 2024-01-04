#include "View.h"
#include <SFML/Graphics.hpp>

View::View() {

}

View::~View() {
    
}

void View::showWindow() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!", sf::Style::Titlebar | sf::Style::Close);
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // request the grid to the controller, which will get it from the model
            
            // base what is shown on the grid

            // check for user input, if so send it to the controller to be treated
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}