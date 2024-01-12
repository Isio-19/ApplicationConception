#ifndef VIEW
#define VIEW

#include <vector>
#include "math.h"

class Controller;

class View {
private:
    Controller* controller;
public:
    View();
    ~View();

    void addController(Controller* _controller);

    void showWindow();
};

#include "Controller.h"

#endif