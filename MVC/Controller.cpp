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
        // change the board        
        int** tempGrid = switchTiles(firstMoveX, firstMoveY, x, y);
        model->changeBoard(tempGrid);
        
        // change the variables
        model->resetMoves();

        // check if the board has a winner
        this->checkBoard();

        // switch player after making sure that the win condition hasn't been achieved
        model->switchPlayer();
    }

    return false;
}

void Controller::cancelMoves() { model->resetMoves(); }

int** Controller::switchTiles(int firstX, int firstY, int secondX, int secondY) {
    int** grid = model->getBoard();

    int temp = (int) model->getCurrentPlayer() +1; 
    // if both moves are aligned on the same line
    if (firstY == secondY) {
        if (firstX < secondX) {
            // shift to the left
            for (int i=firstX; i<secondX; i++) 
                grid[firstY][i] = grid[firstY][i+1];
            grid[firstY][secondX] = temp;

            return grid;
        }

        // shift to the right
        for (int i=firstX; i>secondX; i--) 
            grid[firstY][i] = grid[firstY][i-1];
        grid[firstY][secondX] = temp;

        return grid;
    }

    // both moves are aligned on the same column
    if (firstY < secondY) {
        // shift up
        for (int i=firstY; i<secondY; i++) 
            grid[i][firstX] = grid[i+1][firstX];
        grid[secondY][firstX] = temp;

        return grid;
    }

    // shift down
    for (int i=firstY; i>secondY; i--)
        grid[i][firstX] = grid[i-1][firstX];
    grid[secondY][firstX] = temp;

    return grid;
}

bool Controller::hasFirstMove() { return model->hasFirstMove(); }

int Controller::getFirstMoveX() { return model->getFirstMoveX(); }

int Controller::getFirstMoveY() { return model->getFirstMoveY(); }

void Controller::launch() { view->showWindow(); }

bool Controller::checkBoard() {
    int enemy = 2, current = 1;

    if (model->getCurrentPlayer()) {
        enemy = 1;
        current = 2;
    }

    if (checkWinningPlayer(enemy)) {
        std::cout << "opposite won!" << std::endl;
        return true;
    }

    if (checkWinningPlayer(current)) {
        std::cout << "current won!" << std::endl;
        return true;
    }

    return false;
}

bool Controller::checkWinningPlayer(int player) {
    // if currentPlayer = true, check cross 1
    // else check circle 2
    int squareToCheck = player;
    int** grid = model->getBoard();

    //check lines 
    for (int i=0; i<5; i++) {
        if (squareToCheck == grid[i][0] && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2] && grid[i][2] == grid[i][3] && grid[i][3] == grid[i][4])
            return true;
    }

    //check columns
    for (int i=0; i<5; i++) {
        if (squareToCheck == grid[0][i] && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i] && grid[2][i] == grid[3][i] && grid[3][i] == grid[4][i])
            return true;
    }

    //check diagonals
    if (squareToCheck == grid[0][0] && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[2][2] == grid[3][3] && grid[3][3] == grid[4][4])
        return true;

    if (squareToCheck == grid[4][0] && grid[4][0] == grid[3][1] && grid[3][1] == grid[2][2] && grid[2][2] == grid[1][3] && grid[1][3] == grid[0][4])
        return true;

    return false;
}