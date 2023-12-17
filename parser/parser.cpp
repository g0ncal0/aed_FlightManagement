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

Airports parser::parse_airports(Countries& countries, Cities& cities) {
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
        getline(iss, s_longitude, ',');
        latitude = std::stof(s_latitude);
        longitude = std::stof(s_longitude);

        unsigned char codeCountry = countries.addCountry(country);
        cities.addCity(city, codeCountry);

        airports.addAirport(code, name, city, codeCountry, latitude, longitude);
    }

    file.close();

    return airports;
}
