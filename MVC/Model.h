#ifndef MODEL
#define MODEL

class Controller;

class Model {
    private:
        Controller* controller;

        // 0 Empty 
        // 1 Cross
        // 2 Circle
        int** board;

        // false Cross
        // true  Circle
        bool currentPlayer;

        int firstMoveX;
        int firstMoveY;

    public:
        Model();
        ~Model();

        void addController(Controller* _controller);

        int** getBoard();
        bool getCurrentPlayer();
        bool hasFirstMove();
        int getFirstMoveX();
        int getFirstMoveY();

        void changeBoard(int** nextBoard);
        void switchPlayer();
        void setFirstMove(int x, int y);
        void resetMoves();
};

#include "Controller.h"

#endif