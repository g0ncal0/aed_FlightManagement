//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_AIRPORT_H
#define AVIOES_AIRPORT_H


#include <string>
#include <unordered_set>

class Airport {
private:
    std::string code;
    std::string name;
    unsigned char country;
    float latitude;
    float longitude;

public:
    Airport(std::string code, std::string name, unsigned char country, float latitude, float longitude){
        this->code = code;
        this->name = name;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }
};

class Airports {
private:
    std::unordered_set<Airport> airports;

public:
    void addAirport(std::string code, std::string name, unsigned char country, float latitude, float longitude){
        airports.insert(Airport(code, name, country, latitude, longitude));
    }

};


#endif //AVIOES_AIRPORT_H
