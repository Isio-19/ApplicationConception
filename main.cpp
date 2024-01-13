#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "MVC/Controller.h"

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
    sf::RenderWindow window(sf::VideoMode(600, 600), "Application de conception");

    // grid
    const float offset = 50.0;
    const int SIZE_OF_SQUARE = 100;

    // tiles in the future, associate texture directly
    // 0: empty, 1: cross, 2: circle
    int8_t grid[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };

    // true for Player1 the cross, false for Player2 the circle
    bool playerTurn = true;

    // bool used for the second input of human players
    bool waitingSecondClick = false;

    // initialize the textures
    sf::Texture emptyTexture;
    sf::Texture crossTexture;
    sf::Texture circleTexture;
    try {
        emptyTexture.loadFromFile("sprites/empty.png");
        emptyTexture.setSmooth(true);
        
        crossTexture.loadFromFile("sprites/cross.png");
        crossTexture.setSmooth(true);
        
        circleTexture.loadFromFile("sprites/circle.png");
        circleTexture.setSmooth(true);
    } catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
    }

    // board outline
    std::vector<sf::Vertex> boardOutline;
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset-1), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset+1 + 5*SIZE_OF_SQUARE), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset+1 + 5*SIZE_OF_SQUARE, offset+1 + 5*SIZE_OF_SQUARE), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset + 5*SIZE_OF_SQUARE, offset), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset-1), sf::Color::Black));
    
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            window.clear(sf::Color(224, 224, 215));

            // redraw the grid
            for (int i=0; i<5; i++) {
                for (int j=0; j<5; j++) {
                    sf::Sprite sprite;
                        
                    if (grid[i][j] == 0) {
                        sprite.setTexture(emptyTexture);
                    } else if (grid[i][j] == 1) {
                        sprite.setTexture(circleTexture);
                    } else if (grid[i][j] == 2) {
                        sprite.setTexture(crossTexture);
                    }

                    sprite.setPosition(sf::Vector2f(offset + i*SIZE_OF_SQUARE, offset + j*SIZE_OF_SQUARE));
                    window.draw(sprite);
                }
            }

            // draw the outline of the grid, so that the border have a consistent thickness
            window.draw(&boardOutline[0], boardOutline.size(), sf::LineStrip);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // detect the square with floor((event.mouseButton.x-offset)/sizeSquare) 
                    sf::Sprite sprite;
                    
                    int clickX = floor((event.mouseButton.x-offset)/SIZE_OF_SQUARE);
                    int clickY = floor((event.mouseButton.y-offset)/SIZE_OF_SQUARE);

                    // check if the player clicks in the playable area
                    if (clickX < 0 || clickX > 4 || clickY < 0 || clickY > 4) {
                        std::cout << "Click OOB!!!" << std::endl;
                        continue;
                    }

                    if (clickX > 0 && clickX < 4 && clickY > 0 && clickY < 4) {
                        std::cout << "Click interdit !!!" << std::endl;
                        continue;
                    }
                    std::cout << "a" << std::endl;


                    std::cout << "x: " << clickX << " y: " << clickY << std::endl;
                    
                    // change the grid to the current player's state
                    grid[clickX][clickY] = (int)playerTurn + 1;

                    if (playerTurn)
                        sprite.setTexture(crossTexture, true);
                    else
                        sprite.setTexture(circleTexture, true);

                    window.display();
                   
                    playerTurn = !playerTurn;
                }
            }

        window.display();
        }

        if (waitingSecondClick) {
            std::cout << std::endl;
        }

    }

    return 0;
}
