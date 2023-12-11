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
    Airline(const std::string& code, const std::string& name, const std::string& callsign, unsigned char country){
        this->code = code;
        this->name = name;
        this->callsign = callsign;
        this->country = country;
    }
    std::string getCode() const{return code;}
    std::string getName() const{return name;}
    std::string getCallSign() const{return callsign;}

};

struct airlineHash
{
    // Hash function
    // TODO
    int operator() (const Airline& p) const {
        // FIND HASH FUNCTION APPLICABLE
        int v = 0;
        for (char c : p.getCode()) v = 457 * v + c;
        v %= 457;
        return v;
    }

    // Equality function
    // TODO
    bool operator() (const Airline& p1, const Airline& p2) const {
        return p1.getCode() == p2.getCode();
    }
};

typedef std::unordered_set<Airline, airlineHash, airlineHash> tabHAirline;

class Airlines {
private:
    tabHAirline airlines;

public:
    void addAirline(const std::string& code, const std::string& name, const std::string& callsign, unsigned char country){
        airlines.insert(Airline(code, name, callsign, country));
    }
    tabHAirline getAirlines() {
        return airlines;
    }

};


#endif //AVIOES_AIRLINE_H
