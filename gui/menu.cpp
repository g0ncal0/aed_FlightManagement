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
        if(res >= 0 && res <= 10){
            react(res);
        }
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
    list<std::pair<std::string, std::string>> maximumTrips;

    switch (action) {

        case 0:
            prompt();
            break;

        case 1:
            gui::print("The statistics of the model are the following:");
            gui::printUnstyledlist(model.getStatistics());
            break;

        case 2:
            gui::printFlightList(model.getFlightsOnAirport(gui::getAirport(model.getAirports())), model.getCities() ,model.getAirports());
            break;
        case 3:
            gui::printFlightList(model.getFlightsOnCity(gui::getString("City Name:")), model.getCities() ,model.getAirports());
            break;
        case 4:
            gui::printFlightList(model.getFlightsOfAirline(gui::getString("Airline Code")), model.getCities() ,model.getAirports());
            break;
        case 5:
            gui::printAirports(model.getFlights().bfsmaxXstops(gui::getAirport(model.getAirports()), gui::getInt("How many stops?")));
            break;
        case 6:
            gui::printSourceDestinationAirport(model.maximumTrip(maximumTrips), maximumTrips);
            break;
        case 7:
            gui::print("Please note that to calculate the highest air traffic capacity airport, we counted all arrivals and departures from each company.");
            gui::printWithOrder(model.highestAirTrafficCapacity(gui::getInt("How many")));
            break;

        case 8:
            gui::printAirports(model.essentialAirports());
            break;

        case 10:
            gui::printWithOrder(gui::getAirportsUserChoice(model.getAirports()));
            break;
    }
}
