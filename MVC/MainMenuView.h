#ifndef VIEW
#define VIEW

#include <SFML/Graphics.hpp>
#include <vector>
#include "math.h"

class Controller;

class View {
private:
    Controller* controller;

    sf::RenderWindow* window;
    int offset;
    int sizeSquare;

public:
    View();
    ~View();

    void addController(Controller* _controller);
    void addWindow(sf::RenderWindow* window);

    void drawBoardOutline();
    void drawBoard(int** board);
    void drawSquare(int x, int y, sf::Color color);

    void showWindow();
};

#include "Controller.h"

#endif