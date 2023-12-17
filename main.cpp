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
    parser::parse_flights(flights);

    /*for (const Airline& airline : airlines.getAirlines()) {
        std::cout << airline.getCode() << "              " << airline.getName() << "               " << airline.getCallSign() << std::endl;
    }
    */

    /*for (const Airport& airport : airports.getAirports()) {
        std::cout << airport.getCode() << "              " << airport.getName() << std::setfill(' ') << std::setw(75 - (int)airport.getName().length()) << airport.getCity() << std::endl;
    }*/

    for (Vertex * v : flights.getVertexSet()) {
        for (Edge edge : v->getAdj()) {
            cout << v->getIATA() << "   " << edge.getDest()->getIATA() << "   ";
            bool checkFirst = true;
            for (std::string al : edge.getAirlines()) {
                if (checkFirst) {
                    checkFirst = false;
                    cout << al;
                }
                else cout << "," << al;
            }
            cout << endl;
        }
    }




    /*Model model = Model();
    model.setAirlines(airlines);
    model.setAirports(airports);
    model.setCities(cities);
    model.setCountries(countries);
    menu m = menu(model);*/



    return 0;
}