//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_AIRPORT_H
#define AVIOES_AIRPORT_H


#include <string>
#include <unordered_set>
#include <list>
#include "Airline.h"

class Airport {
private:
    std::string code;
    std::string name;

    std::string city;
    unsigned char country;
    float latitude;
    float longitude;

public:
    Airport(const std::string& code, const std::string& name, const std::string city, unsigned char country, float latitude, float longitude){
        this->code = code;
        this->name = name;
        this->city = city;
        this->country = country;
        this->latitude = latitude;
        this->longitude = longitude;
    }
    std::string getCode() const {return code;}
    std::string getName() const {return name;}
    std::string getCity() const {return city;}
    float getLatitude() const {return latitude;}
    float getLongitude() const {return longitude;}
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
    void addAirport(const std::string& code, const std::string& name, const std::string& city, unsigned char country, float latitude, float longitude){
        airports.insert(Airport(code, name, city, country, latitude, longitude));
    }

    const tabHAirport& getAirports() {
        return airports;
    }

    std::list<Airport> getAirportsOnCity(const std::string& name){
        for(auto airport : airports){
            // Lacks logic, because city is not being stored on airport!
            //if(airport.)
        }
    }

    const Airport& getAirport(const std::string& code) const {
        Airport airport_key(code, "", "", 0, 0, 0);
        return *airports.find(airport_key);
    }

};


#endif //AVIOES_AIRPORT_H
