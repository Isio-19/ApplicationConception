#include "../include/Model.h"
#include "../include/View.h"
#include "../include/Controller.h"
#include <iostream>

int main(int argc, char const *argv[]) {
    Model _m;
    View _v;
    Controller _c;

    _m.addController(&_c);

    _v.addController(&_c);
    _v.addWindow( _c.getWindow() );

    _c.addModel(&_m);
    _c.addView(&_v);

    _c.launch();

    return 0;
}
