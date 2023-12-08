class Tile {
    private:
        int stateOfTile; 

    public:
        Tile();
        ~Tile();

        bool changeState(int state);
};
