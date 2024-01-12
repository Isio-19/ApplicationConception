#include "Controller.h"

#include <iostream>

Controller::Controller() {

}

Controller::~Controller() {

}

void Controller::addModel(Model* _model) { model = _model; }

void Controller::addView(View* _view) { view = _view; }

int** Controller::getGrid() { return model->getBoard(); }

bool Controller::validClick(int x, int y) {
    x = floor((x-50)/100.0);
    y = floor((y-50)/100.0);
    bool currentPlayer = model->getCurrentPlayer();

    // outside the playing area
    if (x < 0 || x > 4 || y < 0 || y > 4) { return false; }

    // inside the playing area but not valid squares
    if (x > 0 && x < 4 && y > 0 && y < 4) { return false; }

    // treat the input
    int currentSquare = model->getBoard()[y][x];

    // check if the clicked square is valid or matches the currentPlayer
    // for first move
    if (!model->hasFirstMove()) {
        if (currentSquare == 0 || (currentSquare == (int)currentPlayer +1)) {
            model->setFirstMove(x, y);
            return true;
        }

        return false;
    }

    // for second move
    // check the clicked square has either the same x or y has the first move, but not both
    int firstMoveX = model->getFirstMoveX();
    int firstMoveY = model->getFirstMoveY();

    if ((firstMoveX == x) != (firstMoveY == y)) {
        model->setSecondMove(x, y);
        switchTiles(firstMoveX, firstMoveY, x, y);
    }

    return false;
}

void Controller::switchTiles(int firstX, int firstY, int secondX, int secondY) {
    int** grid = model->getBoard();

    // if both moves are aligned on the same line
    if (firstY == secondY) {
        int temp = grid[firstY][firstX]; 
        if (firstX < secondX) {
            // shift to the left
            for (int i=firstX; i<secondX; i++) 
                grid[firstY][i] = grid[firstY][i+1];
            grid[firstY][secondX] = temp;

            return;
        }

        // shift to the right
        for (int i=firstX; i>secondX; i--) 
            grid[firstY][i] = grid[firstY][i-1];
        grid[firstY][secondX] = temp;

        return;
    }

    // both moves are aligned on the same column
    int temp = grid[firstY][firstX]; 
    if (firstY < secondY) {
        // shift up
        for (int i=firstY; i<secondY; i++) 
            grid[i][firstX] = grid[i+1][firstX];
        grid[secondY][firstX] = temp;

        return;
    }

    // shift down
    for (int i=firstX; i>secondX; i--) 
        grid[firstY][i] = grid[firstY][i-1];
    grid[firstY][secondX] = temp;

    return;
}

bool Controller::hasFirstMove() { return model->hasFirstMove(); }

void Controller::launch() { view->showWindow(); }