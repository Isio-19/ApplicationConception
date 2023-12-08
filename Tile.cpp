#include "Tile.h"

Tile::Tile() {
    stateOfTile = 0;
}

Tile::~Tile() { }

bool Tile::changeState(int state) {
    if (stateOfTile != 0)
        return false;
    
    stateOfTile = state;
    return true;
}