//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_LOCATION_H
#define AVIOES_LOCATION_H


#include <string>
#include <list>
#include <unordered_set>


typedef std::pair<std::string, unsigned char> parcc;


struct parccHash
{
    // Hash function
    // TODO
    int operator() (const parcc& p) const {
        // FIND HASH FUNCTION APPLICABLE
        return 0;
    }

    // Equality function
    // TODO
    bool operator() (const parcc& p1, const parcc& p2) const {
        if(p1.second == p2.second){
            return true;
        }
        return false;
    }
};



class Cities {
    // Store the name and country
    std::unordered_set<parcc, parccHash, parccHash> cities;

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
        int find = findCountry(country);
        if(find == -1){
            // IT WAS NOT FOUND
            countries.push_back(country);
            lastused++;
        }else{
            // IT WAS FOUND
            return find;
        }

        return lastused--;
    }

    unsigned char findCountry(const std::string& country){
        for(int i = 0; i < countries.size(); i++){
            if(countries[i] == country){
                return i;
            }
        }
        return -1;
    }

};


#endif //AVIOES_LOCATION_H
