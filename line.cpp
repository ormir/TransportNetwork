//
//  line.cpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#include "line.hpp"

Line::Line(std::string n):
name(n) {}

void Line::addStation(Station* s) {
    stations.push_back(s);
}

std::string Line::getName() const { return name; }