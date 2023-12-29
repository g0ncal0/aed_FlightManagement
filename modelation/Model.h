//
// Created by Filipe Correia on 16/12/2023.
//

#ifndef AVIOES_MODEL_H
#define AVIOES_MODEL_H

#include <cmath>
#include <algorithm>
#include "Airport.h"
#include "../graph/graph.h"
#include "../parser/parser.h"
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

    list<string> getStatistics();
    list<flight> getFlightsOfAirline(string airline);

    list<flight> getFlightsOnCity(string city);

    int countriesToWhichTravel(list<flight>& flights);
    list<flight> getFlightsOnAirport(string iata);

    int maximumTrip(list<std::pair<std::string, std::string>>& res);
    unordered_set<std::string> essentialAirports();
    vector<vector<std::string>> bestFlight(const std::string& src, const std::string& dest);
    vector<vector<pair<std::string, vector<std::string>>>> bestFlightWithAirlinesToAvoid(const std::string& src, const std::string& dest, const vector<std::string>& airlinesToAvoid);
    vector<vector<std::string>> bestFlightOptions(const vector<std::string>& sources, const vector<std::string>& destinations);
    vector<vector<pair<std::string, vector<std::string>>>> bestFlightOptionsWithAirlinesToAvoid(const vector<std::string>& sources, const vector<std::string>& destinations, const vector<std::string>& airlinesToAvoid);

    vector<string> highestAirTrafficCapacity(int k);
};


#endif //AVIOES_MODEL_H
