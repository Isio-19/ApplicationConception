#include "Model.h"

#include <iostream>

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

Model::~Model() {
    for (int i = 0; i<5; i++) {
        delete board[i];
    }

    delete board;
}

void Model::addController(Controller* _controller) { controller = _controller; }

int** Model::getBoard() { return board; }

bool Model::getCurrentPlayer() { return currentPlayer; }

int Model::getWinningPlayer() { return winningPlayer; }

bool Model::hasFirstMove() { return firstMoveX != -1; } 

int Model::getFirstMoveX() { return firstMoveX; }

int Model::getFirstMoveY() { return firstMoveY; }


void Model::changeBoard(int** nextBoard) {
    for (int i=0; i<5; i++) 
        for (int j=0; j<5; j++)
            board[i][j] = nextBoard[i][j]; 
}

void Model::switchPlayer() { currentPlayer = !currentPlayer; }

void Model::setWinningPlayer(int winner) { winningPlayer = winner; }

void Model::setFirstMove(int x, int y) {
    firstMoveX = x;
    firstMoveY = y;
}

void Model::resetMoves() {
    firstMoveX = -1;
    firstMoveY = -1;
}
