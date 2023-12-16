//
// Created by Filipe Correia on 16/12/2023.
//

#ifndef AVIOES_MODEL_H
#define AVIOES_MODEL_H


#include "Airport.h"
#include "../graph/graph.h"
#include "Location.h"

struct flight{
    string iata_arrival;
    string iata_departure;
    string airline;
};

class Model {
    Graph flights;
    Airlines airlines;
    Airports airports;
    Countries countries;
    Cities cities;

public:
    void setFlight(Graph f);
    void setAirlines(Airlines a);
    void setAirports(Airports a);
    void setCountries(Countries c);
    void setCities(Cities c);

    Graph getFlights(){return flights;}
    Airlines getAirlines(){return airlines;}
    Airports getAirports(){return airports;}

    double calculateDistance(double lat1, double lon1, double lat2, double lon2);

    list<string> getStatistics();


    list<flight> getFlightsOnAirport(string iata);
};


#endif //AVIOES_MODEL_H
