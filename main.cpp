#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "Controller.h"

// if (event.type == sf::Event::MouseButtonPressed)
//     if (event.mouseButton.button == sf::Mouse::Left) {
//        floor((event.mouseButton.x-offset)/sizeSquare); 
//        floor((event.mouseButton.y-offset)/sizeSquare);
// }

std::vector<sf::Vertex> drawBoardOutline(int offset, int numberSquare, int sizeSquare) {
    std::vector<sf::Vertex> lines;
    
    // horizontal
    lines.push_back(sf::Vertex(sf::Vector2f(offset, offset), sf::Color::Black));
    lines.push_back(sf::Vertex(sf::Vector2f(offset, offset + numberSquare*sizeSquare), sf::Color::Black));

    for (int i=1; i<numberSquare+1; i++) {
        lines.push_back(sf::Vertex(sf::Vector2f(offset + i*sizeSquare, offset), sf::Color::Black));
        lines.push_back(sf::Vertex(sf::Vector2f(offset + i*sizeSquare, offset + numberSquare*sizeSquare), sf::Color::Black));
    }

    // vertical
    lines.push_back(sf::Vertex(sf::Vector2f(offset, offset), sf::Color::Black));
    lines.push_back(sf::Vertex(sf::Vector2f(offset + numberSquare*sizeSquare, offset), sf::Color::Black));

    for (int i=1; i<numberSquare+1; i++) {
        lines.push_back(sf::Vertex(sf::Vector2f(offset, offset + i*sizeSquare), sf::Color::Black));
        lines.push_back(sf::Vertex(sf::Vector2f(offset  + numberSquare*sizeSquare, offset + i*sizeSquare), sf::Color::Black));
    }

    return lines;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "SFML works!");

    // grid
    float offset = 50.0;
    int numberSquare = 5;
    int sizeSquare = 100;

    std::vector<sf::Vertex> lines = drawBoardOutline(offset, numberSquare, sizeSquare);
    
    // true for Player1, false for Player2
    bool playerTurn = true;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // detect the square with floor((event.mouseButton.x-offset)/sizeSquare) 
                    std::cout << "x: " << floor((event.mouseButton.x-offset)/sizeSquare) << std::endl;
                    std::cout << "y: " << floor((event.mouseButton.y-offset)/sizeSquare) << std::endl;
                    std::cout << "Player " << playerTurn << std::endl;
                    playerTurn = !playerTurn;
                }
        }

        window.clear(sf::Color(224, 224, 215));
        window.draw(&lines[0], lines.size(), sf::Lines);
        window.display();
    }

    return 0;
}
