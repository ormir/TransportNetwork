//
//  station.hpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#ifndef station_hpp
#define station_hpp
#define INF 999

#include <stdio.h>
#include <string>
#include <map>

class Station {
    std::string name;
    std::map<Station*, int> neighbours;
    
public:
    Station(std::string);
    void addNeighbour(Station*, int);
    int getDistance(Station*) const;
    std::string getLine() const;
    std::string getName() const;
};

#endif /* station_hpp */
