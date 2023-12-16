cmake_minimum_required(VERSION 3.25)
project(avioes)

set(CMAKE_CXX_STANDARD 11)

add_executable(avioes main.cpp graph/graph.cpp graph/graph.h gui/menu.cpp gui/menu.h gui/gui.h modelation/Airport.h modelation/Airline.h modelation/Location.h parser/parser.h parser/parser.cpp modelation/Model.cpp modelation/Model.h)

