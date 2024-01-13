#ifndef CONTROLLER
#define CONTROLLER

#include "Model.h"
#include "View.h"

class Controller {
    private:
        Model* model;
        View* view;

    public:
        Controller();
        ~Controller();
        
        void addModel(Model* _model);
        void addView(View* _view);
        
        int** getGrid();
        bool validClick(int x, int y);
        bool hasFirstMove();
        void switchTiles(int firstX, int firstY, int secondX, int secondY);
        void launch();
};

#endif