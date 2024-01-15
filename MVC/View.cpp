#include "View.h"
#include <iostream>

/**
 * @brief Construct a new View:: View object
 * 
 */
View::View() {
    controller = nullptr;
    window = nullptr;
    offset = 50;
    sizeSquare = 100;
}

/**
 * @brief Link a Controller to the View
 * 
 * @param _controller 
 */
void View::addController(Controller* _controller) { controller = _controller; }

/**
 * @brief Link the window of the Controller to the View
 * 
 * @param _window 
 */
void View::addWindow(sf::RenderWindow* _window) { window = _window; }

/**
 * @brief Draws an outline around the current board
 * 
 */
void View::drawBoardOutline() {
    std::vector<sf::Vertex> boardOutline;
    
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset-1), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset+1 + 5*sizeSquare), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset+1 + 5*sizeSquare, offset+1 + 5*sizeSquare), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset + 5*sizeSquare, offset), sf::Color::Black));
    boardOutline.push_back(sf::Vertex(sf::Vector2f(offset, offset-1), sf::Color::Black));

    window->draw(&boardOutline[0], boardOutline.size(), sf::LineStrip);
}

/**
 * @brief Draws the board given in argument
 * 
 * @param board 
 */
void View::drawBoard(int** board) {
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

/**
 * @brief Draw a square of the given color at the given coordinates
 * 
 * @param x 
 * @param y 
 * @param color 
 */
void View::drawSquare(int x, int y, sf::Color color) {
    std::vector<sf::Vertex> squareToDraw;
    
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*x + offset, sizeSquare*y+1 + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*(x+1) + offset, sizeSquare*y+1 + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*(x+1) + offset, sizeSquare*(y+1) + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*x + offset+1, sizeSquare*(y+1) + offset), color));
    squareToDraw.push_back(sf::Vertex(sf::Vector2f(sizeSquare*x + offset+1, sizeSquare*y + offset), color));

    window->draw(&squareToDraw[0], squareToDraw.size(), sf::LineStrip);
}

/**
 * @brief Open a window with which the user can interact with
 * 
 */
void View::showWindow() {
    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window->close();

            window->clear(sf::Color(224, 224, 215));
            
            // request the grid to the controller, which will get it from the model
            int** grid = controller->getGrid();

            // base what is shown on the grid
            drawBoardOutline();
            drawBoard(grid);

            if (controller->getWinningPlayer() != 0) {
                // if a winning player is defined, show it
                sf::Font font;
                font.loadFromFile("various/arial.ttf");
                sf::Text text;
                text.setFont(font);
                text.setCharacterSize(50);
                text.setFillColor(sf::Color::Black);
                text.setStyle(sf::Text::Bold);
                text.setPosition(sf::Vector2f(
                    offset,
                    sizeSquare*5 + 2*offset 
                ));

                text.setString("Circle won!");
                if (controller->getWinningPlayer() == 2)
                    text.setString("Cross won!");

                window->draw(text);
            }

            if (controller->hasFirstMove()) {
                // highlight the squares that the user can click forthe second move
                int x = controller->getFirstMoveX();
                int y = controller->getFirstMoveY();

                // highlight squares in which we can do the second move
                drawSquare(0, y, sf::Color::Red);
                drawSquare(4, y, sf::Color::Red);
                drawSquare(x, 0, sf::Color::Red);
                drawSquare(x, 4, sf::Color::Red);

                // highlight the first move square in cyan
                drawSquare(x, y, sf::Color::Cyan);
            }

            // check for user input, if so send it to the controller to be treated
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left)
                    controller->validClick(event.mouseButton.x, event.mouseButton.y);

                // if right click, cancel any moves
                if (event.mouseButton.button == sf::Mouse::Right)
                    controller->cancelMoves();
            }

            // if echap or click on the back button, back to main menu
            // TO DO: second view, main menu
            // TO DO: return to main menu on echap
            // if (event.type == sf::Event::KeyPressed) {
            //     if (event.key.code == sf::Keyboard::Escape) {
            //         std::cout << "the escape key was pressed" << std::endl; 
            //     }
            // }

        window->display();
        }
    }
}
