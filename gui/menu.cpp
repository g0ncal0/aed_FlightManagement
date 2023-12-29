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
        if(res >= 0 && res <= 12){
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
                    "Countries Listing",
                    "Airlines Listing",
                    "Airports Listing"
                    });

}

void menu::preparebestflight(){
    vector<std::string> sources;
    vector<std::string> destinations;
    vector<std::string> airlinesToAvoid;

    gui::print("Source airport(s):");

    sources = gui::getAirportsUserChoice(model.getAirports(), model.getCities());

    gui::print("Destination airport(s):");

    destinations = gui::getAirportsUserChoice(model.getAirports(), model.getCities());

    airlinesToAvoid = gui::getAirlinesToAvoid();

    if (airlinesToAvoid.empty()) gui::printVectorOfVectorOfFlights(model.bestFlightOptions(sources, destinations));
    else gui::printVectorOfVectorOfFlightsWithAirlines(model.bestFlightOptionsWithAirlinesToAvoid(sources, destinations, airlinesToAvoid));

}

void menu::prepareMaxTrip(){
    list<std::pair<std::string, std::string>> maximumTrips;
    gui::printSourceDestinationAirport(model.maximumTrip(maximumTrips), maximumTrips);

}

/**
 * The function that calls all other action methods of the model
 * @param action which action to make
 */
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
            gui::printFlightList(model.getFlightsOnAirport(gui::getAirport(model.getAirports())), model.getCities() ,model.getAirports());
            break;
        case 3:
            gui::printFlightList(model.getFlightsOnCity(gui::getCity(model.getCities()), model.getCities()), model.getCities() ,model.getAirports());
            break;
        case 4:
            gui::printFlightList(model.getFlightsOfAirline(gui::getString("Airline Code")), model.getCities() ,model.getAirports());
            break;
        case 5:
            gui::printAirports(model.getFlights().bfsmaxXstops(gui::getAirport(model.getAirports()), gui::getInt("How many stops?")));
            break;
        case 6:
            prepareMaxTrip();
            break;
        case 7:
            gui::print("Please note that to calculate the highest air traffic capacity airport, we counted all arrivals and departures from each company.");
            gui::printWithOrder(model.highestAirTrafficCapacity(gui::getInt("How many")));
            break;

        case 8:
            gui::printAirports(model.essentialAirports());
            break;
        case 9:
            preparebestflight();
            break;
        case 10:
            gui::print("CODE : NAME");
            gui::printVector(model.getCountries().getCountries());
            break;
        case 11:
            gui::printAirlines(model.getAirlines());
            break;
        case 12:
            gui::printAirportsModel(model.getAirports());
            break;

    }
}
