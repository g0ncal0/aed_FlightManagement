//
// Created by goncalo on 07-12-2023.
//

#ifndef AVIOES_PARSER_H
#define AVIOES_PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include "../modelation/Airline.h"
#include "../modelation/Airport.h"
#include "../modelation/Location.h"
#include "../modelation/Model.h"


class parser {
public:
    static Airlines parse_airlines(Countries& countries);
    static Airports parse_airports(Countries& countries, Cities& cities, Graph& flights);
    static void parse_flights(Graph& flights, const Airports& airports);

private:

};


#endif //AVIOES_PARSER_H
