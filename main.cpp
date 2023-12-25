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

    /*for (const Airline& airline : airlines.getAirlines()) {
        std::cout << airline.getCode() << "              " << airline.getName() << "               " << airline.getCallSign() << std::endl;
    }
    */

    /*for (const Airport& airport : airports.getAirports()) {
        std::cout << airport.getCode() << "              " << airport.getName() << std::setfill(' ') << std::setw(75 - (int)airport.getName().length()) << airport.getCity() << std::endl;
    }*/

    /*for (Vertex * v : flights.getVertexSet()) {
        for (Edge edge : v->getAdj()) {
            cout << v->getIATA() << "   " << edge.getDest()->getIATA() << "   " << edge.getWeight() << "   ";
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
    }*/



    Model model = Model();
    model.setAirlines(airlines);
    model.setAirports(airports);
    model.setCities(cities);
    model.setCountries(countries);
    model.setFlight(flights);
    menu m = menu(model);

    /*ifstream f("../dataset/airports.csv");

    // Cria uma lista para armazenar as cidades
    set<string> cities1;

    // Lê o ficheiro linha a linha
    string line;
    getline(f, line);
    while (getline(f, line)) {
        // Extrai a cidade
        string city;
        std::istringstream iss(line);
        getline(iss, city, ',');
        getline(iss, city, ',');
        getline(iss, city, ',');

        //cout << city << endl;
        //return 0;

        // Adiciona a cidade à lista se não estiver presente
        if (cities1.find(city) == cities1.end()) {
            cities1.insert(city);
        }
        else cout << city << endl;
    }

    // Imprime o número de cidades
    cout << cities1.size() << endl;*/

    return 0;
}
