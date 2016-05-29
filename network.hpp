//
//  network.hpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#ifndef network_hpp
#define network_hpp

#include <stdio.h>
#include <map>
#include <queue>
#include <vector>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include "station.hpp"

class Network {
    std::map<std::string, Station*> stations;
    
public:
    Network();
    Network(std::string);
    void import(std::string);
    Station* addStation(std::string, std::string);
    bool path(std::string, std::string);
    void info() const;
    void help() const;
    ~Network();
};

#endif /* network_hpp */
