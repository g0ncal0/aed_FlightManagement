//
// Created by Filipe Correia on 07/12/2023.
//

#include <iostream>
#include "menu.h"


menu::menu() {
    gui::print("HELLO!");
    gui::printlist({"first", "second"});
    int res = gui::getInt("What's your option");
}

void menu::prompt() {
    gui::print("Here are your options.");

}

