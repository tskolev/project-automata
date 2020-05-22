#include <iostream>
#include "State.h"

int main() {
    std::cout << "Hello, World!" << std::endl;

    State st1("q0");
    State st(st1);

    return 0;
}
