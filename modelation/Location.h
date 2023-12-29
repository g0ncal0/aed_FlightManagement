//
// Created by Filipe Correia on 07/12/2023.
//

#ifndef AVIOES_LOCATION_H
#define AVIOES_LOCATION_H


#include <string>
#include <list>
#include <unordered_set>


typedef std::pair<std::string, unsigned char> parcc;

struct parccHash
{
    // Hash function
    int operator() (const parcc& p) const {
        // FIND HASH FUNCTION APPLICABLE
        int v = 0;
        for (char c : p.first) v = 3271 * v + c;
        v %= 3271;
        return v;
    }

    // Equality function

    bool operator() (const parcc& p1, const parcc& p2) const {
        if(p1.first == p2.first){
            return true;
        }
        return false;
    }
};


typedef  std::unordered_set<parcc, parccHash, parccHash> unsetcities;


class Cities {
    // Store the name and country
    unsetcities cities;

public:
    std::vector<std::string> getCitiesOnCountry(int country);
    void addCity(std::string name, unsigned char country){
        cities.insert(parcc(name, country));
    }

    bool doesCityExist(std::string cityname) const{
        auto it = cities.find({cityname, 0});
        if(it != cities.end()){
            return true;
        }
        return false;
    }

    unsigned char getCountry(std::string city){
        std::vector<unsigned char> country;
        for(auto c : cities){
            if(c.first == city){
                country.push_back(c.second);
            }
        }
        if(country.empty()){
            return 0;
        }
        if(country.size() == 1){
            return country[0];
        }else{
            std::cout << "There are " << country.size() << " cities with the same name.";
            for(auto c : country){
                std::cout << "Country code: " << c << std::endl;
            }
            std::cout << "Which country do you choose?";
            unsigned char given;
            std::cin >> given;
            if(given >= 0 && given < country.size() ){
                return given;
            }
            return country[0];
        }
    }


    unsetcities getCities(){return cities;}
    unsigned char getCountry(std::string city) const{
        auto c = cities.find(parcc(city, 0));
        return c->second;
    }
};

class Countries {
private:
// THINK ABOUT THE DATA STRUCTURE HERE
    std::vector<std::string> countries;
    unsigned char lastused = 0;

public:
    int addCountry(const std::string& country){
        int find = findCountry(country);
        if(find == -1){
            // IT WAS NOT FOUND
            countries.push_back(country);
            lastused++;
        }else{
            // IT WAS FOUND
            return find;
        }

        return lastused--;
    }

    int findCountry(const std::string& country){
        for(int i = 0; i < countries.size(); i++){
            if(countries[i] == country){
                return i;
            }
        }
        return -1;
    }
    std::vector<std::string> getCountries(){return countries;}

};





#endif //AVIOES_LOCATION_H
