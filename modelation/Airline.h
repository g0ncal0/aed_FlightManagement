//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_AIRLINE_H
#define AVIOES_AIRLINE_H

#include <string>
#include <unordered_set>

class Airline {
private:
    std::string code;
    std::string name;
    std::string callsign;
    unsigned char country;

public:
    Airline(std::string code, std::string name, std::string callsign, unsigned char country){
        this->code = code;
        this->callsign = callsign;
        this->callsign = callsign;
        this->country = country;
    }
    std::string getCode(){return code;}
    std::string getName(){return name;}
    std::string getCallSign(){return callsign;}

};

class Airlines {
private:
    std::unordered_set<Airline> airlines;

public:
    void addAirline(const std::string& code, const std::string& name, const std::string& callsign, unsigned char country){
        airlines.insert(Airline(code, name, callsign, country));
    }

};


#endif //AVIOES_AIRLINE_H
