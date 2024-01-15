#include "Model.h"

#include <iostream>

/**
 * @brief Construct a new Model:: Model object
 * 
 */
Model::Model() {
    controller = nullptr;

    board = new int*[5];
    for (int i = 0; i<5; i++) {
        board[i] = new int[5];

        for (int j = 0; j<5; j++)
            board[i][j] = 0;
    }

    currentPlayer = true;
    winningPlayer = 0;

    firstMoveX = -1;
    firstMoveY = -1;
}

/**
 * @brief Destroy the Model:: Model object
 * 
 */
Model::~Model() {
    for (int i = 0; i<5; i++) {
        delete board[i];
    }

    delete board;
}

/**
 * @brief Link a Controller to the Model
 * 
 * @param _controller 
 */
void Model::addController(Controller* _controller) { controller = _controller; }

/**
 * @brief Return the current board to the Controller
 * 
 * @return int** 
 */
int** Model::getBoard() { return board; }

/**
 * @brief Return the current player
 * 
 * @return true 
 * @return false 
 */
bool Model::getCurrentPlayer() { return currentPlayer; }

/**
 * @brief Return the winning player
 * 
 * @return int 
 */
int Model::getWinningPlayer() { return winningPlayer; }

/**
 * @brief Return the current first move
 * 
 * @return true 
 * @return false 
 */
bool Model::hasFirstMove() { return firstMoveX != -1; } 

/**
 * @brief Return the x coordinate of the first move
 * 
 * @return int 
 */
int Model::getFirstMoveX() { return firstMoveX; }

/**
 * @brief Return the y coordinate of the first move
 * 
 * @return int 
 */
int Model::getFirstMoveY() { return firstMoveY; }

/**
 * @brief Change the current board to the board given in argument
 * 
 * @param nextBoard 
 */
void Model::changeBoard(int** nextBoard) {
    for (int i=0; i<5; i++) 
        for (int j=0; j<5; j++)
            board[i][j] = nextBoard[i][j]; 
}

/**
 * @brief Switch the current player
 * 
 */
void Model::switchPlayer() { currentPlayer = !currentPlayer; }

/**
 * @brief Set the winning player
 * 
 * @param winner 
 */
void Model::setWinningPlayer(int winner) { winningPlayer = winner; }

/**
 * @brief Set the current move
 * 
 * @param x 
 * @param y 
 */
void Model::setFirstMove(int x, int y) {
    firstMoveX = x;
    firstMoveY = y;
}

/**
 * @brief Reset the move that is store in the Model
 * 
 */
void Model::resetMoves() {
    firstMoveX = -1;
    firstMoveY = -1;
}
