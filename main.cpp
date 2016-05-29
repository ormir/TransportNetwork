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
    std::string input;
    
    //if the main function gets two parameteres which is the name of the program and the file name then do this
    if (argc == 2) {
        net = new Network(argv[1]);
//        net->info();
//        net->path("Michelbeuern-AKH", "Karlsplatz");
//    } else {
//        std::cout << "filename missing" << std::endl;
    }else{
        net = new Network();
    }
    
    std::cout << "Transportation Network" << std::endl;
    std::cout << "Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved." << std::endl;
    std::cout << "Type 'help' for more information" << std::endl;
    
    while(true){
        std::getline(std::cin,input);
        
        if(input == "import"){
            std::string file;
            std::getline(std::cin,file);
            net->import(file);
        }else if (input == "info"){
            net->info();
            
        }else if (input == "help"){
            net->help();
        } else if (input == "search"){
            std::string start, finish;
            std::cout << "Choose your starting point: " << std::endl;
            std::getline(std::cin,start);
            std::cout << "Choose your destination: " << std::endl;
            std::getline(std::cin,finish);
            net->path(start,finish);
        }else if (input == "exit"){
            break;
        }else {
            std::cout << "Command '" << input << "' not recognized" << std::endl;
            std::cout << "Type 'help' for more information" << std::endl;
         }
    }
    
    if (net != nullptr) delete net;
    return 0;
}
