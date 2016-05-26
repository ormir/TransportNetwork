//
//  line.hpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#ifndef line_hpp
#define line_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "station.hpp"

class Line {
    std::string name;
    std::vector<Station*> stations;
public:
    Line(std::string);
    void addStation(Station*);
    std::string getName() const;
};

#endif /* line_hpp */
