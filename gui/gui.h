//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_GUI_H
#define AVIOES_GUI_H


#include <iostream>

#include <list>
#include "../modelation/Model.h"

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

    static void printFlightList(const list<flight>& flights){
        std::cout << "\nDEP  " << "ARR  " << "AIRL\n";
        std::cout << "-------------\n";
        list<std::string> airlinesfound;
        list<std::string> destinationsfound;
        for(auto& f : flights){
            std::cout << f.iata_departure << "  " << f.iata_arrival << "  " << f.airline << "\n";
            if(find(airlinesfound.begin(), airlinesfound.end(), f.airline) == airlinesfound.end()){
                airlinesfound.push_back(f.airline);
            }
            if(std::find(destinationsfound.begin(), destinationsfound.end(), f.iata_arrival) == destinationsfound.end()){
                destinationsfound.push_back(f.iata_arrival);
            }
        }

        std::cout << "Total of " << flights.size() << " flights, operated by " << airlinesfound.size() << " different airlines and with " << destinationsfound.size() << " different destinations.\n";

    }
};


#endif //AVIOES_GUI_H
