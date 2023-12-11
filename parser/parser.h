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


class parser {

Airlines parse_airline();
Airports parse_students();
};


#endif //AVIOES_PARSER_H
