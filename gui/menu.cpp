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
            gui::printFlightList(model.getFlightsOnAirport(gui::getString("Airport's IATA")));
            break;
        case 3:
            // TO IMPLEMENT: SOUNDS COMPLICATED
            break;
        case 4:
            gui::printFlightList(model.getFlightsOfAirline(gui::getString("Airline Code")));
            break;
        case 5:


    }
}
