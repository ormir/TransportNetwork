//
//  main.cpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#include <iostream>
#include "network.hpp"

int main(int argc, const char * argv[]) {
    
    Network* net = nullptr;
    
    if (argc == 2) {
        net = new Network(argv[1]);
        net->info();
    } else {
        std::cout << "filename missing" << std::endl;
    }
    
    if (net != nullptr) delete net;
    return 0;
}
