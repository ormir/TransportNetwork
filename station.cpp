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
//std::string Station::getLine() const { return line->getName(); }

void Station::addNeighbour(Station* nStation, int distance) {
    neighbours[nStation] = distance;
}


int Station::getDistance(Station* nStation) const {
    try {
        return neighbours.at(nStation);
    } catch (std::out_of_range e) {
        return INF;
    }
}
