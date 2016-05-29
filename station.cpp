//
//  station.cpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#include "station.hpp"

Station::Station(std::string n):
name(n) {}

std::string Station::getName() const { return name; }
std::string Station::getLine() const { return line; }
std::map<Station*, int> Station::getNeighbours() const { return neighbours; }

//adds neighbour to the map that contains all references to the neighbours
void Station::addNeighbour(Station* nStation, int distance) {
    neighbours[nStation] = distance;
}


int Station::getDistance(Station* nStation) const {
    try {
        //try to get the distance of the neighbour at 'nStation'
        return neighbours.at(nStation);
        //if distance or station not found, return 'INF' = a number representing infinity
    } catch (std::out_of_range e) {
        return INF;
    }
}

//function to add the metro lines to the stations such as U1, U2, etc in case there are more than just one line
void Station::addLine(const std::string nLine) {
    if(line.empty()) line = nLine;
    else {
        line.append(", ");
        line.append(nLine);
    }
}

//function to display all the stations of the transportation network
void Station::info() {
    std::cout << name << " (" << line << ")" << std::endl;
    for (auto it = neighbours.begin(); it != neighbours.end(); ++it) {
        std::cout << '\t' << it->second << " min to " << it->first->getName() << " (" << it->first->getLine() << ")" << std::endl;
    }
}
