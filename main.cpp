#include <iostream>
#include "gui/menu.h"
#include "parser/parser.h"

int main() {
    //menu m = menu();

    Countries countries;
    Airlines airlines = parser::parse_airlines(countries);

    for (const Airline& airline : airlines.getAirlines()) {
        std::cout << airline.getCode() << "              " << airline.getName() << "               " << airline.getCallSign() << std::endl;
    }

    return 0;
}