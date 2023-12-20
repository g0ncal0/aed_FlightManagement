//
// Created by Filipe Correia on 16/12/2023.
//

#ifndef AVIOES_MODEL_H
#define AVIOES_MODEL_H

#include <cmath>
#include <algorithm>
#include "Airport.h"
#include "../graph/graph.h"
#include "Location.h"

struct flight{
    string iata_departure;
    string iata_arrival;
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
    Cities getCities(){return cities;}
    static double calculateDistance(double lat1, double lon1, double lat2, double lon2);

    list<string> getStatistics();
    list<flight> getFlightsOfAirline(string airline);

    list<flight> getFlightsOnCity(string city);

    int countriesToWhichTravel(list<flight>& flights);
    list<flight> getFlightsOnAirport(string iata);
};


#endif //AVIOES_MODEL_H
