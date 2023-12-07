//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_LOCATION_H
#define AVIOES_LOCATION_H


#include <string>
#include <list>


class City {

};

class Countries {
private:
// THINK ABOUT THE DATA STRUCTURE HERE
    std::vector<std::string> countries;
    static int lastused;
public:
    Countries(){
        lastused = 0;
    }
    int addCountry(const std::string& country){
        if(std::find(countries.begin(), countries.end(), country) == countries.end()){
            countries.push_back(country);
            lastused++;
        }
    }

};


#endif //AVIOES_LOCATION_H
