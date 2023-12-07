//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_LOCATION_H
#define AVIOES_LOCATION_H


#include <string>
#include <list>
#include <unordered_set>


typedef std::pair<std::string, unsigned char> parcc;

class Cities {
    // Store the name and country
    std::unordered_set<parcc> cities;

public:
    std::vector<std::string> getCitiesOnCountry(int country);
    void addCity(std::string name, unsigned char country){
        cities.insert(parcc(name, country));
    }
};

class Countries {
private:
// THINK ABOUT THE DATA STRUCTURE HERE
    std::vector<std::string> countries;
    unsigned char lastused = 0;

public:
    unsigned char addCountry(const std::string& country){
        if(std::find(countries.begin(), countries.end(), country) == countries.end()){
            countries.push_back(country);
            lastused++;
        }
        return lastused--;
    }

};


#endif //AVIOES_LOCATION_H
