//
// Created by Filipe Correia on 07/12/2023.
//

#include <iostream>
#include "menu.h"


menu::menu(Model& model) {
    gui::print("HELLO!");
    this->model = model;
    prompt();
    while(true){
        int res = gui::getInt("What's your option");
        if(res == -1){
            break;
        }
        react(res);
    }
}

void menu::prompt() {
    gui::print("Here are your options.");
    gui::printlist({"Repeat Instructions",
                    "Global Statistics",
                    "Flights Of An Airport (inc. number of flights, number of airlines, number of destinations, )",
                    "Flights By City",
                    "Flights By Airline",
                    "Reachable airports with max of X stops",
                    "Maximum trip",
                    "The greatest air traffic capacity airport",
                    "Essential Airports",
                    "Best Flight",
                    });

}

void menu::react(int action){
    switch (action) {

        case 0:
            prompt();
            break;

        case 1:
            gui::print("The statistics of the model are the following:");
            gui::printUnstyledlist(model.getStatistics());
            break;

        case 2:
            gui::printFlightList(model.getFlightsOnAirport(gui::getString("Airport's IATA")), model.getCities() ,model.getAirports());
            break;
        case 3:
            gui::printFlightList(model.getFlightsOnCity(gui::getString("City Name:")), model.getCities() ,model.getAirports());
            break;
        case 4:
            gui::printFlightList(model.getFlightsOfAirline(gui::getString("Airline Code")), model.getCities() ,model.getAirports());
            break;
        case 5:
            break;
        case 6:
            list<std::pair<std::string, std::string>> maximumTrips;
            gui::printSourceDestinationAirport(model.maximumTrip(maximumTrips), maximumTrips);
            break;
    }
}
