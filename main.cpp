#include <iostream>
#include <iomanip>
#include "gui/menu.h"
#include "parser/parser.h"

int main() {


    Countries countries;
    Cities cities;
    Airlines airlines = parser::parse_airlines(countries);
    Airports airports = parser::parse_airports(countries, cities);

    /*for (const Airline& airline : airlines.getAirlines()) {
        std::cout << airline.getCode() << "              " << airline.getName() << "               " << airline.getCallSign() << std::endl;
    }
    */
    for (const Airport& airport : airports.getAirports()) {
        std::cout << airport.getCode() << "              " << airport.getName() << std::setfill(' ') << std::setw(75 - (int)airport.getName().length()) << airport.getCity() << std::endl;
    }


    /*Model model = Model();
    model.setAirlines(airlines);
    model.setAirports(airports);
    model.setCities(cities);
    model.setCountries(countries);
    menu m = menu(model);*/



    return 0;
}