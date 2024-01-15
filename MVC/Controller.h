#ifndef CONTROLLER
#define CONTROLLER

#include "Model.h"
#include "View.h"
#include <SFML/Graphics.hpp>

class Controller {
    private:
        Model* model;
        View* view;

        sf::RenderWindow* window;

    public:
        Controller();
        ~Controller();
        
        void addModel(Model* _model);
        void addView(View* _view);
        
        sf::RenderWindow* getWindow();
        int** getGrid();
        bool validClick(int x, int y);
        void cancelMoves();

        bool hasFirstMove();
        int getFirstMoveX();
        int getFirstMoveY();

        int** switchTiles(int firstX, int firstY, int secondX, int secondY);

        void launch();

        bool checkBoard();
        bool checkWinningPlayer(int player);

};

#endif