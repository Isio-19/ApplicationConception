#include "MVC/Model.h"
#include "MVC/View.h"
#include "MVC/Controller.h"
#include <iostream>

int main(int argc, char const *argv[]) {
    Model _m;
    View _v;
    Controller _c;

    _m.addController(&_c);
    _v.addController(&_c);

    _c.addModel(&_m);
    _c.addView(&_v);

    _c.launch();

    return 0;
}
