//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_AIRPORT_H
#define AVIOES_AIRPORT_H


#include <string>
#include <unordered_set>
#include "Airline.h"

class Airport {
private:
    std::string code;
    std::string name;

    //std::string city;
    unsigned char country;
    float latitude;
    float longitude;

public:
    Airport(const std::string& code, const std::string& name, unsigned char country, float latitude, float longitude){
        this->code = code;
        this->name = name;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    std::string getCode() const {return code;}
    std::string getName() const {return name;}
};

struct airportHash
{
    // Hash function
    int operator() (const Airport& p) const {
        // FIND HASH FUNCTION APPLICABLE
        int v = 0;
        for (char c : p.getCode()) v = 457 * v + c;
        v %= 457;
        return v;
    }

    // Equality function
    bool operator() (const Airport& p1, const Airport& p2) const {
        return p1.getCode() == p2.getCode();
    }
};

typedef std::unordered_set<Airport, airportHash, airportHash> tabHAirport;

class Airports {
private:
    tabHAirport airports;


public:
    void addAirport(std::string code, std::string name, unsigned char country, float latitude, float longitude){
        airports.insert(Airport(code, name, country, latitude, longitude));
    }

    const tabHAirport& getAirports() {
        return airports;
    }

//    std::list<Airport> getAirportsOnCity(std::string name){
//        for(auto airport : airports){
            // Lacks logic, because city is not being stored on airport!
            //if(airport.)
 //       }
//    }

};


#endif //AVIOES_AIRPORT_H
