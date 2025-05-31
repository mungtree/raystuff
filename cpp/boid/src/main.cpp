#include <iostream>
#include "mugengine.hpp"

int main(int argv, char** argc) {
    MugEngine me = MugEngine();
    me.debug();
    std::cout << "Hello World!\n";
}
