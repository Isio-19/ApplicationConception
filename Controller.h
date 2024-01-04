#ifndef CONTROLLER
#define CONTROLLER

#include "Model.h"
#include "View.h"

class Controller {
    private:
        Model* model;
        View* view;

    public:
        Controller(Model* _model, View* _view);
        ~Controller();

        void launch();
};

#endif