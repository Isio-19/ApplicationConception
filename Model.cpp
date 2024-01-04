#include "Model.h"

Model::Model() {
    board = new int*[5];
    for (int i = 0; i<5; i++) {
        board[i] = new int[5];

        for (int j = 0; j<5; j++)
            board[i][j] = 0;
    }
}

Model::~Model() {
    for (int i = 0; i<5; i++) {
        delete board[i];
    }

    delete board;
}

int** Model::getBoard() {
    return board;
}