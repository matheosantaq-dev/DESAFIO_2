#include <iostream>
#include <ctime>
#include <cstdlib>

#include "Menu.h"

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    Menu menu;
    menu.iniciar();

    return 0;
}
