#include "View.h"
#include <SFML/Graphics.hpp>
#include <iostream>

int boardOffset = 50;

View::View() {

}

View::~View() {
    
}
    
void View::addController(Controller* _controller) { controller = _controller; }

void drawBoardOutline(int offset, int sizeSquare, sf::RenderWindow* window) {
    std::vector<sf::Vertex> boardOutline;
    
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset-1), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset+1 + 5*sizeSquare), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset+1 + 5*sizeSquare, offset+1 + 5*sizeSquare), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset + 5*sizeSquare, offset), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset-1), sf::Color::Black));

    window->draw(&boardOutline[0], boardOutline.size(), sf::LineStrip);
}
void drawBoard(int** board, sf::RenderWindow* window, int offset) {
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
    
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            sf::Sprite sprite;
                
            if (board[i][j] == 0) {
                sprite.setTexture(emptyTexture);
            } else if (board[i][j] == 1) {
                sprite.setTexture(circleTexture);
            } else if (board[i][j] == 2) {
                sprite.setTexture(crossTexture);
            }

            sprite.setPosition(sf::Vector2f(offset + j*100, offset + i*100));
            window->draw(sprite);
        }
    }

}

void drawSquare(int x, int y, int offset, int sizeSquare, sf::Color color, sf::RenderWindow* window) {
    std::vector<sf::Vertex> squareToDraw;
    
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*x + offset, sizeSquare*y+1 + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*(x+1) + offset, sizeSquare*y+1 + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*(x+1) + offset, sizeSquare*(y+1) + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*x + offset+1, sizeSquare*(y+1) + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*x + offset+1, sizeSquare*y + offset), color));

    window->draw(&squareToDraw[0], squareToDraw.size(), sf::LineStrip);
}

void View::showWindow() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Application de conception", sf::Style::Titlebar | sf::Style::Close);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear(sf::Color(224, 224, 215));
            
            // request the grid to the controller, which will get it from the model
            int** grid = controller->getGrid();

            // base what is shown on the grid
            // drawBoardOutline(boardOffset, 100, &window);
            drawBoard(grid, &window, boardOffset);

            if (controller->hasFirstMove()) {
                // highlight the squares that the user can click forthe second move
                int x = controller->getFirstMoveX();
                int y = controller->getFirstMoveY();

                // highlight squares in which we can do the second move
                drawSquare(0, y, boardOffset, 100, sf::Color::Red, &window);
                drawSquare(4, y, boardOffset, 100, sf::Color::Red, &window);
                drawSquare(x, 0, boardOffset, 100, sf::Color::Red, &window);
                drawSquare(x, 4, boardOffset, 100, sf::Color::Red, &window);

                // highlight the first move square in cyan
                drawSquare(x, y, boardOffset, 100, sf::Color::Cyan, &window);
            }

            // check for user input, if so send it to the controller to be treated
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    controller->validClick(event.mouseButton.x, event.mouseButton.y);

                // if right click, cancel any moves
                if (event.mouseButton.button == sf::Mouse::Right)
                    controller->cancelMoves();

                // if echap or click on the back button, back to main menu
                
                // TO DO: second view, main menu
                // TO DO: return to main menu on echap
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key == sf::Keyboard::Escape) {
                    std::cout << "the escape key was pressed" << std::endl; 
                }
            }

        window.display();
    }
}
