//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_GUI_H
#define AVIOES_GUI_H


#include <iostream>

#include <list>

class gui {

public:
    static void print(const char* s){
        std::cout << s << '\n';
    }
    static void printlist(const std::list<std::string>& list){
        int i = 0;
        for(const auto& el : list){
            std::cout << i << " : " << el << '\n';
            i++;
        }
        std::cout << '\n';
    }
    static void printUnstyledlist(const std::list<std::string>& list){

        for(const auto& el : list){
            std::cout <<"> " << el << '\n';
        }
        std::cout << '\n';
    }

    static int getInt(const char* s){
        std::cout << s << ": ";
        int res;
        std::cin >> res;
        return res;
    }
    static std::string getString(const char* s){
        std::cout << s << ": ";
        std::string res;
        std::cin >> res;
        return res;
    }
};


#endif //AVIOES_GUI_H
