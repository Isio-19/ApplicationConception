#ifndef MODEL
#define MODEL

class Model {
    private:
        int** board;

    public:
        Model(/* args */);
        ~Model();

        int** getBoard();
};

#endif