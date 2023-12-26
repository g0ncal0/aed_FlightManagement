//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_GUI_H
#define AVIOES_GUI_H


#include <iostream>
#include <algorithm>
#include <list>
#include "../modelation/Model.h"

class gui {

public:
    static void print(const char* s){
        std::cout << s << '\n';
    }
    static void printlist(const std::list<std::string>& list){
        int i = 0;
        for(const auto& el : list){
            std::cout << i << " : " << el << '\n';
            i++;
        }
        std::cout << '\n';
    }
    static void printUnstyledlist(const std::list<std::string>& list){

        for(const auto& el : list){
            std::cout <<"> " << el << '\n';
        }
        std::cout << '\n';
    }

    static int getInt(const char* s){
        while(true){
        std::cout << s << ": ";
        std::string res;
        std::cin >> res;
        try{
            int r = stoi(res);
            return r;
        }catch(invalid_argument){
            std::cout << "Invalid number\n";
        }
        }
    }
    static std::string getString(const char* s){
        std::cout << s << ": ";
        std::string res;
        std::cin >> res;
        return res;
    }

    static void printFlightList(const list<flight>& flights, const Cities& cities, const Airports& airports){
        std::cout << "\nDEP  " << "ARR  " << "AIRL\n";
        std::cout << "-------------\n";
        list<std::string> airlinesfound;
        list<std::string> destinationsfound;
        list<std::string> arrivalsfound;
        list<unsigned char> countriesfound;
        list<std::string> citiesfound;
        for(auto& f : flights){
            std::cout << f.iata_departure << "  " << f.iata_arrival << "  " << f.airline << "\n";

            if(std::find(airlinesfound.begin(), airlinesfound.end(), f.airline) == airlinesfound.end()){
                airlinesfound.push_back(f.airline);
            }

            if(std::find(destinationsfound.begin(), destinationsfound.end(), f.iata_arrival) == destinationsfound.end()){
                destinationsfound.push_back(f.iata_arrival);
            }

            if(std::find(arrivalsfound.begin(), arrivalsfound.end(), f.iata_departure) == arrivalsfound.end()){
                arrivalsfound.push_back(f.iata_departure);
            }

            std::string city = airports.getAirport(f.iata_arrival).getCity();
            unsigned char country = cities.getCountry(city);

            if(std::find(countriesfound.begin(), countriesfound.end(), country) == countriesfound.end()){
                countriesfound.push_back(country);
            }

            if(std::find(citiesfound.begin(), citiesfound.end(), city) == citiesfound.end()){
                citiesfound.push_back(city);
            }
        }

        std::cout << "Total of " << flights.size() << " flights, from "<< arrivalsfound.size() << " airports, operated by " << airlinesfound.size() << " different airlines and with " << destinationsfound.size() << " different destinations.\n";
        std::cout << "These destinations span from " << countriesfound.size() << " countries and " << citiesfound.size() << " cities.\n";
    }

    static std::string getAirport(const Airports& airports){
        std::string given;

        while(true){
            std::cout << "Airport: ";
            std:: cin >> given;
            if(airports.airportExists(given)){
                break;
            }
            std::cout << "NOT VALID\n";
        }

        return given;

    }

    static void printSourceDestinationAirport(int stops, const list<std::pair<std::string, std::string>>& airportsPairs){
        std::cout << "\nSRC  " << "DST\n";
        std::cout << "--------\n";

        for (const std::pair<std::string, std::string>& par : airportsPairs) {
            std::cout << par.first << "  " << par.second << std::endl;
        }

        std::cout << "These are the maximum trips with " << stops << " stops.\n\n";
    }

    static void printAirports(const unordered_set<std::string>& airports) {
        for (const std::string& airport : airports) cout << airport << endl;
        cout << "Results in " << airports.size() << " airports";
        cout << endl;
    }

    static void printWithOrder(const vector<std::string>& printing){
        for(int i = 0; i < printing.size(); i++){
            std::cout << i + 1  << "º > " << printing[i] << endl;
        }
    }
};


#endif //AVIOES_GUI_H
