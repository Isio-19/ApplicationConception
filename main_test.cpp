#include "Model.h"
#include "View.h"
#include "Controller.h"
#include <iostream>

int main(int argc, char const *argv[]) {
    Model _m;
    View _v;

    Controller _c(&_m, &_v);
    _c.launch();

    std::cout << "Fuck out" << std::endl;

    return 0;
}
