# Description of the project

The main objective of this project is precisely to develop a
flight management system for the air travel network of the airlines around the world that provides effective
assistance to users who wish to explore and plan travel.


## TECHNICAL

Edges need to have information about airlines in a list.



## How are locations referred

- Airport Code or name;
- City Name - should encapsulate all airports from a given city
- Geographical coordinates - consider closest airports to the coordinates given

Have a function that returns a list of airports according to users preference.

- 457 is prime after 444



## TO-DO

- Read and parse the provided data.  
This includes loading the airports, airlines and connections into an appropriate graph data structure
- Develop a menu with management system:
- Calculate stats:
  - Global number of airports and number of available flights;
  - Number of flights out of an airport; and from how many different airlines;
  - Number of flights per city/airline;
  - Number of different countries that a given airport/city flies to;
  - Number of destinations (airports, cities or countries) available for a given airport
  - Number of reachable destinations (airports, cities or countries) from a given airport in a
    maximum number of X stops (lay-overs);
  - Maximum trip and corresponding pair of source-destination airports (or pairs, if more than
    one), that is, the flight trip(s) with the greatest number of stops in between them;
  - Identify the top-k airport with the greatest air traffic capacity, that is, with the greatest number
    of flights;
  - Identify the airports that are essential to the network’s circulation capability (airports are
    essential if, when removed, areas of the network start to be unreachable)
- Present best flight options (or set of options for a given source and destination)
    - Allow using filters (subset of nodes/edges) that respect user preferences.


- Doxygen



