#include <iostream>
#include "gui/menu.h"
#include "parser/parser.h"

int main() {
    //menu m = menu();

    Countries countries;
    Cities cities;
    Airlines airlines = parser::parse_airlines(countries);
    Airports airports = parser::parse_airports(countries, cities);

    for (const Airline& airline : airlines.getAirlines()) {
        std::cout << airline.getCode() << "              " << airline.getName() << "               " << airline.getCallSign() << std::endl;
    }
    for (const Airport& airport : airports.getAirports()) {
        std::cout << airport.getCode() << "              " << airport.getName() << "               " << std::endl;
    }

    return 0;
}