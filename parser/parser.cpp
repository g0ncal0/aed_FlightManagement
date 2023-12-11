//
// Created by goncalo on 07-12-2023.
//

#include "parser.h"

Airlines parse_airlines(Countries& countries) {
    std::ifstream classes("air.csv");
    std::string line;

    Airlines airlines;
    std::string trash;
    getline(classes, trash);

    if (!classes.is_open()) {
        std::cout << "not ok";
        return airlines;
    }

    while (getline(classes,line))
    {
        std::istringstream iss(line);

        std::string code, name, callSign, country;

        getline(iss, code, ',');
        getline(iss, name, ',');
        getline(iss, callSign, ',');
        getline(iss, country, ',');

        unsigned char codeCountry = countries.addCountry(country);
        airlines.addAirline(code, name, callSign, codeCountry);
    }

    classes.close();

    return airlines;
}
