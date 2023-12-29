//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_GUI_H
#define AVIOES_GUI_H


#include <iostream>
#include <algorithm>
#include <list>
#include "../modelation/Model.h"

using namespace std;

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
    static float getFloat(const char* s){
        std::cout << s << ": ";
        float res;
        std::cin >>res;
        return res;
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


    static vector<std::string> getAirportsUserChoice(const Airports& airports){
        print("How do you want to refer to the airport(s)?");
        printlist({"IATA", "City Name", "Geographic Coordinates"});

        int g;
        std::cin >> g;
        if(g == 0){
            return {getAirport(airports)};
        }
        if(g == 1){
            std::string city = getString("In which city");
            return airports.getAirportsInCity(city);
        }
        if(g == 2){
            float lat = getFloat("Latitude");
            float lon = getFloat("Longitude");
            return airports.getAirportsOnCoordinates(lat, lon);
        }
        vector<string> r;
        return r;
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

    static vector<std::string> getAirlinesToAvoid() {
        vector<std::string> res;
        std::string answer;

        cout << "Do you have any restrictions with the airlines? (y/n)  ";
        cin >> answer;
        if (answer == "n") return res;

        cout << "\nDo you want to:\n  1) Minimize the number of different airlines\n  2) Avoid some specific airlines\n";
        cin >> answer;
        if (answer == "1") return {"MINIMIZE"};

        while (answer != "n") {
            cout << "Write one airline code or 'n' if you are done. \n";
            cin >> answer;
            if (answer != "n") res.push_back(answer);
        }

        return res;
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

    static void printVectorOfVectorOfFlights(const vector<vector<std::string>>& options) {
        if (options.empty()) {
            cout << "There is no option available" << endl;
            return;
        }

        for (int i = 1; i <= options.size(); i++) {
            const vector<std::string>& aux = options[i-1];
            cout << "Option " << i << ":\n";

            for (int j = 0; j < aux.size(); j++) {
                if (j != 0) cout << " -> ";
                cout << aux[j];
            }
            cout << "\n\n";
        }
    }

    static void printVectorOfVectorOfFlightsWithAirlines(const vector<vector<pair<std::string, vector<std::string>>>>& options) {
        if (options.empty()) {
            cout << "There is no option available" << endl;
            return;
        }

        for (int i = 1; i <= options.size(); i++) {
            const vector<pair<std::string, vector<std::string>>>& aux = options[i-1];

            cout << "Option " << i << ":\n";

            for (int j = 0; j < aux.size(); j++) {
                vector<std::string> airlines = aux[j].second;

                if (j != 0) {
                    cout << " -> [" << airlines[0];
                    for (int k = 1; k < airlines.size(); k++) cout << "," << airlines[k];
                    cout << "] -> ";
                }
                cout << aux[j].first;
            }
            cout << "\n\n";
        }
    }

    static void printVectorOfVectorOfFlightsWithAirlines2(const vector<vector<pair<std::string, std::string>>>& options) {
        if (options.empty()) {
            cout << "There is no option available" << endl;
            return;
        }

        for (int i = 1; i <= options.size(); i++) {
            const vector<pair<std::string, std::string>>& aux = options[i-1];

            cout << "Option " << i << ":\n";

            for (int j = 0; j < aux.size(); j++) {

                if (j != 0) cout << " -> [" << aux[j].second << "] -> ";
                cout << aux[j].first;
            }
            cout << "\n\n";
        }
    }
};


#endif //AVIOES_GUI_H
