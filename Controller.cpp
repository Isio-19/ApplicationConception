#include "Controller.h"

Controller::Controller(Model* _model, View* _view) {
    model = _model;
    view = _view;
}

Controller::~Controller() {
    delete model;
    delete view;
}

void Controller::launch() {
    view->showWindow();
}