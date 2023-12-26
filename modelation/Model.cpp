//
// Created by Filipe Correia on 16/12/2023.
//

#include <iostream>
#include "Model.h"

void Model::setFlight(Graph f) {
    flights = f;
}

void Model::setAirlines(Airlines a) {
    airlines = a;
}

void Model::setAirports(Airports a) {
    airports = a;
}
void Model::setCountries(Countries c) {
    countries = c;
}
void Model::setCities(Cities c) {
    cities = c;
}

list<flight> Model::getFlightsOnAirport(string iata) {
    auto destinations = flights.findVertex(iata)->getAdj();
    list<flight> res;
    for(auto d : destinations){
        for(auto airline : d.getAirlines()){
            flight f = {iata,d.getDest()->getIATA(), airline};
            res.push_back(f);
        }

    }
    return res;
}

int Model::countriesToWhichTravel(list<flight>& flights){
    list<unsigned char> countriesknown;
    for(auto f : flights){
        string city = airports.getAirport(f.iata_arrival).getCity();
        unsigned char country = cities.getCountry(city);
        if(std::find(countriesknown.begin(), countriesknown.end(),country) != countriesknown.end()){
            countriesknown.push_back(country);
        }
    }
    return countriesknown.size();
}



list<flight> Model::getFlightsOfAirline(string airline){
    list<flight> res;
    for(Vertex* airport : flights.getVertexSet()){
        for(auto f : airport->getAdj()){
            if(f.getAirlines().find(airline) != f.getAirlines().end()){
                flight r = {airport->getIATA(), f.getDest()->getIATA(), airline};
                res.push_back(r);
            }
        }
    }
    return res;
}

list<flight> Model::getFlightsOnCity(string city){
    list<flight> res;
    for(Vertex* airport : flights.getVertexSet()){
        if(airports.getAirport(airport->getIATA()).getCity() == city){
            for(auto& f : airport->getAdj()){
                for(auto air : f.getAirlines()){
                    res.push_back(flight{airport->getIATA(), f.getDest()->getIATA(),air});
                }
            }
        }
    }
    return res;
}


list<string> Model::getStatistics() {
    list<string> res;

    res.push_back("There are " + to_string(flights.countEdges()) + " flight routes");
    res.push_back("There are " + to_string(airports.getAirports().size()) + " airports");
    res.push_back("There are " + to_string(cities.getCities().size()) + " cities");
    res.push_back("There are " + to_string(countries.getCountries().size()) + " countries");
    res.push_back("There are " + to_string(airlines.getAirlines().size()) + " airlines");
    return res;
}


double toRadians(double degree) {
    return degree * (M_PI / 180.0);
}


double Model::calculateDistance(double lat1, double lon1, double lat2, double lon2) {

    const double earthRadius = 6371.0;

    // Convert latitude and longitude from degrees to radians
    lat1 = toRadians(lat1);
    lon1 = toRadians(lon1);
    lat2 = toRadians(lat2);
    lon2 = toRadians(lon2);

    // Calculate differences in coordinates
    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;

    // Haversine formula
    double a = std::sin(dlat / 2.0) * std::sin(dlat / 2.0) +
               std::cos(lat1) * std::cos(lat2) *
               std::sin(dlon / 2.0) * std::sin(dlon / 2.0);

    double c = 2.0 * std::atan2(std::sqrt(a), std::sqrt(1.0 - a));

    return earthRadius * c;
}

int Model::maximumTrip(list<std::pair<std::string, std::string>>& res) {
    vector<string> destinations;
    int maxStops = 0;
    int auxStops;

    for (Vertex* v : flights.getVertexSet()) {
        auxStops = flights.getDiameter(v, destinations);
        if (auxStops > maxStops) {
            maxStops = auxStops;
            res.clear();
            for (const string& dest : destinations) res.emplace_back(v->getIATA(), dest);
        }
        else if (auxStops == maxStops) {
            for (const string& dest : destinations) res.emplace_back(v->getIATA(), dest);
        }
    }

    return maxStops;
}

unordered_set<std::string> Model::essentialAirports() {
    unordered_set<std::string> essentialAirports = flights.articulationPoints();
    parser::parse_flights(flights, airports);
    return essentialAirports;
}