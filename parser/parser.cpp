//
// Created by goncalo on 07-12-2023.
//

#include "parser.h"

Airlines parser::parse_airlines(Countries& countries) {
    std::ifstream file("../dataset/airlines.csv");
    std::string line;

    Airlines airlines;
    std::string trash;
    getline(file, trash);

    if (!file.is_open()) {
        std::cout << "not ok";
        return airlines;
    }

    while (getline(file, line))
    {
        std::istringstream iss(line);

        std::string code, name, callSign, country;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callSign, ',');
        getline(iss, country, '\r');

        unsigned char codeCountry = countries.addCountry(country);
        airlines.addAirline(code, name, callSign, codeCountry);
    }

    file.close();

    return airlines;
}

Airports parser::parse_airports(Countries& countries, Cities& cities, Graph& flights) {
    std::ifstream file("../dataset/airports.csv");
    std::string line;

    Airports airports;
    std::string trash;
    getline(file, trash);

    if (!file.is_open()) {
        std::cout << "not ok";
        return airports;
    }

    while (getline(file, line))
    {
        std::istringstream iss(line);

        std::string code, name, city, country, s_latitude, s_longitude;
        float latitude, longitude;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, city, ',');
        getline(iss, country, ',');
        getline(iss, s_latitude, ',');
        getline(iss, s_longitude, '\r');
        latitude = std::stof(s_latitude);
        longitude = std::stof(s_longitude);

        unsigned char codeCountry = countries.addCountry(country);
        cities.addCity(city, codeCountry);

        airports.addAirport(code, name, city, codeCountry, latitude, longitude);
        flights.addVertex(code);
    }

    file.close();

    return airports;
}

void parser::parse_flights(Graph& flights, const Airports& airports) {
    std::ifstream file("../dataset/flights.csv");
    std::string line;

    std::string trash;
    getline(file, trash);

    if (!file.is_open()) {
        std::cout << "not ok";
        return;
    }

    while (getline(file, line))
    {
        std::istringstream iss(line);

        std::string source, destination, airline;

        getline(iss, source, ',');
        getline(iss, destination, ',');
        getline(iss, airline, '\r');

        Vertex * airport_src = flights.findVertex(source);
        if (airport_src == NULL) continue;
        bool checkFlight = false;
        for (Edge& edge : airport_src->getAdj()) {
            if (edge.getDest()->getIATA() == destination) {
                checkFlight = true;
                edge.addAirline(airline);
                break;
            }
        }
        if (!checkFlight) {
            Vertex * airport_dest = flights.findVertex(destination);
            if (airport_dest == NULL) continue;
            const Airport& infoAirportSrc = airports.getAirport(source);
            const Airport& infoAirportDest = airports.getAirport(destination);
            Edge edge(airport_dest, Model::calculateDistance(infoAirportSrc.getLatitude(), infoAirportSrc.getLongitude(), infoAirportDest.getLatitude(), infoAirportDest.getLongitude()));
            edge.addAirline(airline);
            airport_src->addAdj(edge);
        }
    }

    file.close();
}
