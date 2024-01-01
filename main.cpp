#include <iostream>
#include <iomanip>
#include "gui/menu.h"
#include "parser/parser.h"

int main() {
    Countries countries;
    Cities cities;
    Graph flights;
    Airlines airlines = parser::parse_airlines(countries);
    Airports airports = parser::parse_airports(countries, cities, flights);
    parser::parse_flights(flights, airports);

    Model model = Model();
    model.setAirlines(airlines);
    model.setAirports(airports);
    model.setCities(cities);
    model.setCountries(countries);
    model.setFlight(flights);

    menu m = menu(model);

    return 0;
}
