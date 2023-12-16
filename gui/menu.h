//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_MENU_H
#define AVIOES_MENU_H


#include "gui.h"
#include "../modelation/Model.h"

class menu {

private:
    Model model;

    void prompt();
    void react(int action);

public:
    menu(Model& model);


};


#endif //AVIOES_MENU_H
