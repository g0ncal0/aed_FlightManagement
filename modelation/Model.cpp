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
        unsigned char country = cities.getCountryApprox(city);
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
            auto airl = f.getAirlines();
            if(airl.find(airline) != airl.end()){
                flight r = {airport->getIATA(), f.getDest()->getIATA(), airline};
                res.push_back(r);
            }
        }
    }
    return res;
}

/**
 * Get the flights on a city by traversing all flights and checking if they are in the city
 * @param city
 * @param cities
 * @return
 */
list<flight> Model::getFlightsOnCity(string city, const Cities& cities){
    list<flight> res;
    unsigned char country = cities.getCountry(city);

    for(Vertex* airport : flights.getVertexSet()){
        if(airports.getAirport(airport->getIATA()).getCity() == city && airports.getAirport(airport->getIATA()).getCountry() == country){
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






/**
 * Function to discover the maximum number of stops between two airports and get this trips. O(V * (V + E))
 * @param res where all the possible maximum trips will be stored
 * @return the maximum number of stopsS
 */
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

/**
 * Function to discover all the essential airports, this means, when removed, areas of the network start to be unreachable. O(V + E)
 * @return the codes of all the essential airports
 */
unordered_set<std::string> Model::essentialAirports() {
    Graph temp = flights.clone();
    unordered_set<std::string> essentialAirports = temp.articulationPoints();
    return essentialAirports;
}

/**
 * Function to discover the k airports with the highest air traffic capacity. O(V + E)
 * @param k the number of airports we want to see
 * @return the k airports' codes with highest air traffic capacity
 */
vector<std::string> Model::highestAirTrafficCapacity(int k){
    flights.setDefaults();
    for(Vertex* v : flights.getVertexSet()){
        int outflights = 0;
        for(auto &out : v->getAdj()){
            outflights += out.getAirlines().size();
        }
        v->setNum(v->getNum() + outflights);
        for(Edge e : v->getAdj()){

            e.getDest()->setNum(e.getDest()->getNum() + e.getAirlines().size());
        }
    }
    vector<std::string> res;
    for(int i = 0; i < k; i++){
        int max = 0;
        std::string cmax;
        for(Vertex* v : flights.getVertexSet()){
            if(v->getNum() > max && find(res.begin(), res.end(), v->getIATA()) == res.end()){
                cmax = v->getIATA();
                max = v->getNum();
            }
        }
        res.push_back(cmax);
    }
    return res;
}

/**
 * Function to find the best flights from airport with code src to airport with code dest. O(V + E)
 * @param src the code of the source airport
 * @param dest the code of the destination airport
 * @return a vector with all the best options for this flight
 */
vector<vector<std::string>> Model::bestFlight(const std::string& src, const std::string& dest) {
    vector<vector<std::string>> res;


    flights.setDefaults();

    Vertex * vertex_src = flights.findVertex(src);
    vertex_src->setVisited(true);

    queue<pair<Vertex *, vector<std::string>>> q;
    q.push({vertex_src, {vertex_src->getIATA()}});

    bool check_done = false;

    while (!q.empty() && !check_done) {
        int level_size = (int) q.size();

        vector<Vertex *> processing;

        for (int i = 0; i < level_size; i++) {
            pair<Vertex *, vector<std::string>> visiting = q.front();
            q.pop();
            Vertex * vertex = visiting.first;

            for (const Edge& edge : vertex->getAdj()) {
                if (edge.getDest()->getIATA() == dest) {
                    check_done = true;
                    visiting.second.push_back(dest);
                    res.push_back(visiting.second);
                }

                else if (!edge.getDest()->isVisited()) {
                    edge.getDest()->setVisited(true);
                    edge.getDest()->setProcessing(true);
                    processing.push_back(edge.getDest());

                    vector<string> path;
                    for (const std::string& airport : visiting.second) path.push_back(airport);
                    path.push_back(edge.getDest()->getIATA());
                    q.push({edge.getDest(), path});
                }

                else if (edge.getDest()->isProcessing()) {
                    vector<string> path;
                    for (const std::string& airport : visiting.second) path.push_back(airport);
                    path.push_back(edge.getDest()->getIATA());
                    q.push({edge.getDest(), path});
                }
            }
        }

        for (Vertex * v : processing) v->setProcessing(false);
    }

    return res;
}

/**
 * Function to find the best flights from airport with codes in vector sources to airports with codes in vector destinations.
 * @param sources the codes of the source airports
 * @param destinations the codes of the destination airports
 * @return a vector with all the best options for this flight
 */
vector<vector<std::string>> Model::bestFlightOptions(const vector<std::string>& sources, const vector<std::string>& destinations) {
    vector<vector<std::string>> res;

    vector<vector<std::string>> aux;
    for (const std::string& source : sources) {
        for (const std::string& destination : destinations) {
            aux = bestFlight(source, destination);
            res.insert(res.end(), aux.begin(), aux.end());
        }
    }


    return res;
}

/**
 * Function to find the best flights from airport with code src to airport with code dest avoiding some airlines. O(V + E)
 * @param src the code of the source airport
 * @param dest the code of the destination airport
 * @param airlinesToAvoid the codes of airlines to avoid
 * @return a vector with all the best options for this flight
 */
vector<vector<pair<std::string, vector<std::string>>>> Model::bestFlightWithAirlinesToAvoid(const std::string& src, const std::string& dest, const vector<std::string>& airlinesToAvoid) {
    vector<vector<pair<std::string, vector<std::string>>>> res;

    flights.setDefaults();

    Vertex * vertex_src = flights.findVertex(src);
    vertex_src->setVisited(true);

    queue<pair<Vertex *, vector<pair<std::string, vector<std::string>>>>> q;
    q.push({vertex_src, {{vertex_src->getIATA(), {}}}});

    bool check_done = false;

    while (!q.empty() && !check_done) {
        int level_size = (int) q.size();

        vector<Vertex *> processing;

        for (int i = 0; i < level_size; i++) {
            pair<Vertex *, vector<pair<std::string, vector<std::string>>>> visiting = q.front();
            q.pop();
            Vertex * vertex = visiting.first;

            for (const Edge& edge : vertex->getAdj()) {
                vector<std::string> allowedAirlines;

                if (edge.getDest()->getIATA() == dest) {

                    for (const std::string& airline : edge.getAirlines()) {
                        bool check = true;
                        for (const std::string& avoid : airlinesToAvoid) {
                            if (airline == avoid) {
                                check = false;
                                break;
                            }
                        }

                        if (check) allowedAirlines.push_back(airline);
                    }

                    if (!allowedAirlines.empty()) {
                        check_done = true;
                        visiting.second.emplace_back(dest, allowedAirlines);
                        res.push_back(visiting.second);
                    }
                }

                else if (!edge.getDest()->isVisited()) {
                    vector<pair<std::string, vector<std::string>>> path;

                    for (const auto& pair : visiting.second) path.push_back(pair);

                    for (const std::string& airline : edge.getAirlines()) {

                        bool check = true;
                        for (const std::string& avoid : airlinesToAvoid) {
                            if (airline == avoid) {
                                check = false;
                                break;
                            }
                        }

                        if (check) allowedAirlines.push_back(airline);
                    }

                    path.emplace_back(edge.getDest()->getIATA(), allowedAirlines);

                    if (!allowedAirlines.empty()) {
                        edge.getDest()->setVisited(true);
                        edge.getDest()->setProcessing(true);
                        processing.push_back(edge.getDest());
                        q.emplace(edge.getDest(), path);
                    }
                }

                else if (edge.getDest()->isProcessing()) {
                    vector<pair<std::string, vector<std::string>>> path;

                    for (const auto& pair : visiting.second) path.push_back(pair);

                    for (const std::string& airline : edge.getAirlines()) {
                        bool check = true;
                        for (const std::string& avoid : airlinesToAvoid) {
                            if (airline == avoid) {
                                check = false;
                                break;
                            }
                        }

                        if (check) allowedAirlines.push_back(airline);
                    }

                    path.emplace_back(edge.getDest()->getIATA(), allowedAirlines);

                    if (!allowedAirlines.empty()) {
                        q.emplace(edge.getDest(), path);
                    }
                }
            }
        }

        for (Vertex * v : processing) v->setProcessing(false);
    }

    return res;
}

vector<vector<pair<std::string, vector<std::string>>>> Model::bestFlightOptionsWithAirlinesToAvoid(const vector<std::string>& sources, const vector<std::string>& destinations, const vector<std::string>& airlinesToAvoid) {
    vector<vector<pair<std::string, vector<std::string>>>> res;

    vector<vector<pair<std::string, vector<std::string>>>> aux;
    for (const std::string& source : sources) {
        for (const std::string& destination : destinations) {
            aux = bestFlightWithAirlinesToAvoid(source, destination, airlinesToAvoid);
            res.insert(res.end(), aux.begin(), aux.end());
        }
    }

    return res;
}

vector<vector<pair<std::string, std::string>>> Model::bestFlightWithMinimumAirlines_aux(const std::string& src, const std::string& dest) {
    vector<vector<pair<std::string, std::string>>> res;

    for (Vertex * vertex : flights.getVertexSet()) {
        vertex->setVisited(false);
        vertex->setProcessing(false);
    }

    Vertex * vertex_src = flights.findVertex(src);
    vertex_src->setVisited(true);

    queue<pair<Vertex *, vector<pair<std::string, std::string>>>> q;
    q.push({vertex_src, {{vertex_src->getIATA(), ""}}});

    bool check_done = false;

    while (!q.empty() && !check_done) {
        int level_size = (int) q.size();

        vector<Vertex *> processing;

        for (int i = 0; i < level_size; i++) {
            pair<Vertex *, vector<pair<std::string, std::string>>> visiting = q.front();
            q.pop();
            Vertex * vertex = visiting.first;

            for (const Edge& edge : vertex->getAdj()) {

                if (edge.getDest()->getIATA() == dest) {
                    check_done = true;

                    for (const std::string& airline : edge.getAirlines()) {
                        vector<pair<std::string, std::string>> aux;
                        for (const auto& par : visiting.second) aux.push_back(par);
                        aux.emplace_back(dest, airline);
                        res.push_back(aux);
                    }
                }

                else if (!edge.getDest()->isVisited()) {
                    edge.getDest()->setVisited(true);
                    edge.getDest()->setProcessing(true);
                    processing.push_back(edge.getDest());

                    for (const std::string& airline : edge.getAirlines()) {
                        vector<pair<std::string, std::string>> path;
                        for (const auto& pair : visiting.second) path.push_back(pair);
                        path.emplace_back(edge.getDest()->getIATA(), airline);
                        q.emplace(edge.getDest(), path);
                    }
                }

                else if (edge.getDest()->isProcessing()) {
                    for (const std::string& airline : edge.getAirlines()) {
                        vector<pair<std::string, std::string>> path;
                        for (const auto& pair : visiting.second) path.push_back(pair);
                        path.emplace_back(edge.getDest()->getIATA(), airline);
                        q.emplace(edge.getDest(), path);
                    }
                }
            }
        }

        for (Vertex * v : processing) v->setProcessing(false);
    }

    return res;
}

/**
 * Function to find the best flights from airport with code src to airport with code dest with the minimum number of different airlines. O(V + E)
 * @param sources the codes of the source airports
 * @param destinations the codes of the destination airports
 * @return a vector with all the best options for this flight
 */
vector<vector<pair<std::string, std::string>>> Model::bestFlightWithMinimumAirlines(const vector<std::string>& sources, const vector<std::string>& destinations) {
    vector<vector<pair<std::string, std::string>>> allOptions;

    vector<vector<pair<std::string, std::string>>> aux;
    for (const std::string& source : sources) {
        for (const std::string& destination : destinations) {
            aux = bestFlightWithMinimumAirlines_aux(source, destination);
            allOptions.insert(allOptions.end(), aux.begin(), aux.end());
        }
    }

    int minimumAirlines = INT_MAX;

    vector<vector<pair<std::string, std::string>>> res;
    for (const vector<pair<std::string, std::string>>& option : allOptions) {
        set<std::string> differentAirlines;
        for (const pair<std::string, std::string>& par : option) differentAirlines.insert(par.second);

        if (differentAirlines.size() < minimumAirlines) {
            minimumAirlines = differentAirlines.size();
            res.clear();
            res.push_back(option);
        }

        else if (differentAirlines.size() == minimumAirlines) res.push_back(option);
    }

    return res;
}
