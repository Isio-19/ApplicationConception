#include "../include/Controller.h"

#include <iostream>

/**
 * @brief Construct a new Controller:: Controller object
 * 
 */
Controller::Controller() {
    window = new sf::RenderWindow(sf::VideoMode(600, 750), "Application de conception", sf::Style::Titlebar | sf::Style::Close);
}

/**
 * @brief Link a Model to the Controller
 * 
 * @param _model 
 */
void Controller::addModel(Model* _model) { model = _model; }

/**
 * @brief Link a View to the Controller
 * 
 * @param _view 
 */
void Controller::addView(View* _view) { view = _view; }

/**
 * @brief Return the window of the Controller, to switch views without getting a close window effect
 * 
 * @return sf::RenderWindow* 
 */
sf::RenderWindow* Controller::getWindow() { return window; }

/**
 * @brief Return the grid of the Model to the View
 * 
 * @return int** 
 */
int** Controller::getGrid() { return model->getBoard(); }

/**
 * @brief Check if the click made on View is valid
 * 
 * @param x 
 * @param y 
 * @return true 
 * @return false 
 */
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
    
    if (((y == 0) || (y == 4)) && y == firstMoveY)
        if (x != 0 && x != 4)
            return false;

    if (((x == 0) || (x == 4)) && x == firstMoveX)
        if (y != 0 && y != 4)
            return false;

    if ((firstMoveX == x) != (firstMoveY == y)) {
        // change the board        
        int** tempGrid = switchTiles(firstMoveX, firstMoveY, x, y);
        model->changeBoard(tempGrid);
        
        // change the variables
        model->resetMoves();

        // check if the board has a winner
        int winner = checkBoard();
        if (winner != 0)
            model->setWinningPlayer(winner);

        // switch player after making sure that the win condition hasn't been achieved
        model->switchPlayer();
    }

    return false;
}

/**
 * @brief Cancel the moves that are saved in the Model
 * 
 */
void Controller::cancelMoves() { model->resetMoves(); }

/**
 * @brief Caclulate the grid for when the tiles from secondMove are moved to firstMove
 * 
 * @param firstX 
 * @param firstY 
 * @param secondX 
 * @param secondY 
 * @return int** 
 */
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

/**
 * @brief Return the state of the first move in the Model
 * 
 * @return true 
 * @return false 
 */
bool Controller::hasFirstMove() { return model->hasFirstMove(); }

/**
 * @brief Get the first move's x coordinate
 * 
 * @return int 
 */
int Controller::getFirstMoveX() { return model->getFirstMoveX(); }

/**
 * @brief Get the first move's y coordinate
 * 
 * @return int 
 */
int Controller::getFirstMoveY() { return model->getFirstMoveY(); }

/**
 * @brief Launch the view's window
 * 
 */
void Controller::launch() { view->showWindow(); }

/**
 * @brief Get the winning player of the Model
 * 
 * @return int 
 */
int Controller::getWinningPlayer() { return model->getWinningPlayer(); }

/**
 * @brief Check the board for any winning moves
 * 
 * @return int 
 */
int Controller::checkBoard() {
    int enemy = 2, current = 1;

    if (model->getCurrentPlayer()) {
        enemy = 1;
        current = 2;
    }

    if (checkWinningPlayer(enemy)) 
        return enemy;

    if (checkWinningPlayer(current)) 
        return current;

    return 0;
}

/**
 * @brief Check if the given player has a winning configuration on the board
 * 
 * @param player 
 * @return true 
 * @return false 
 */
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