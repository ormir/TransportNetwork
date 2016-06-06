//
//  network.cpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#include "network.hpp"

Network::Network() {}

Network::Network(std::string filename) {
    import(filename);
}

bool Network::path(std::string bName, std::string eName) {
    // find begin and end station
    Station *source, *destination;
    try {
        //make sure that the given starting point and destination are part of the network
        source = stations.at(bName);
        destination = stations.at(eName);
        //if the stations were not found, output this:
    } catch (std::out_of_range e) {
        std::cout << "Couldn't find begin or end station" << std::endl;
        return false;
    }
    
    //creating a pointer that points at the source which is the starting point
    Station * head = source;
    
    //the class pair is pairing together these two different values: int and a pointer
    //we only need the int value which we access with "first"
    //auto cmp is part of priority queue below
    auto cmp = [](std::pair<int, Station*> left, std::pair<int, Station*> right) {
        return left.first > right.first;
    };
    
    //here we create a queue that stores all the visited stations between 'source' and 'destination' (given from the user)
    //all the elements in the priority queue are ordered by cmp condition -> left.first > right.first
    std::priority_queue<std::pair<int, Station*>, std::vector<std::pair<int, Station*>>, decltype(cmp)> queue(cmp);
    queue.push(std::make_pair(0, source));
    
    //creating a set for all the visited nodes aka stations
    //creating a map for the distances
    std::set<Station*> visited;
    std::map<Station*, int> dist;
    dist[source] = 0;
    
    while (!queue.empty()) {
        //head is always the current node that we're on. here it becomes the first station of the queue
        head = queue.top().second;
        if (head == destination) break;
        //remove the first node in the queue
        queue.pop();
        //go over the while loop again and again until it reaches the last node in the set called visited
        if (visited.find(head) != visited.end()) continue;
        //insert head into the set if it is not part of the visited stations yet
        visited.insert(head);
        
        // Iterate Neighbours
        //gets all neighbours from map neighbours of Station(head)
        std::map<Station*, int> nbList = head->getNeighbours();
        for (auto nb = nbList.begin(); nb != nbList.end(); ++nb) {
            // Check if distance is already saved
            auto dis = dist.find(nb->first);
            
            // Distance update
            int newDis = dist[head] + head->getDistance(nb->first);
            
            //if the new distance is shorter than the older distance, new distance is added to dist
            //new dis = distance from source to current + to neighbour
            //dist[nb->first] = distance from source to neighbour
            if (dis == dist.end() || newDis < dist[nb->first]) {
                dist[nb->first] = newDis;
                queue.push(std::make_pair(head->getDistance(nb->first), nb->first));
            }
        }
    }
    
    
    
    // Show shortest path (reverse iteration)
    std::cout << "It takes " << dist[head] << " min from " << source->getName() << " to " << destination->getName() << std::endl;
    std::string wayyy = head->getName();
    while (head != source) {
        Station * nbShort = nullptr;
        
        // Get neighbour with shortest path to source
        std::map<Station*, int> nbList = head->getNeighbours();
        for (auto nb = nbList.begin(); nb != nbList.end(); ++nb) {
            if (dist.find(nb->first) == dist.end()) continue;
            else if (nbShort == nullptr) nbShort = nb->first;
            else if (dist[nbShort] > dist[nb->first]) nbShort = nb->first;
        }
        
        wayyy = nbShort->getName()+ " -> " + wayyy;
        head = nbShort;
    }
    
    std::cout << wayyy << std::endl;
    
    return false;
}

void Network::import(std::string filename) {
    std::fstream file(filename);
    
    if(file.is_open()){
        std::string fline, val, lineName;
        int distance = 0;
        while (!file.eof()) {
            // Get file line
            std::getline(file, fline);
            std::stringstream lineStream(fline);
            
            // Get network line name
            std::getline(lineStream, lineName, ':');
            
            // Get first station of line
            std::getline(lineStream, val, '"');
            std::getline(lineStream, val, '"');
            Station* stat = addStation(val, lineName);
            
            // Get stations of network line
            while (!lineStream.eof()) {
                // Distance to other station
                std::getline(lineStream, val, '"');
                try {
                    distance = stoi(val);
                } catch(std::invalid_argument e){
                    continue;
                }
                
                // Get neighbour station
                std::getline(lineStream, val, '"');
                Station * nStat = addStation(val, lineName);
                
                // Neighbour stations
                stat->addNeighbour(nStat, distance);
                nStat->addNeighbour(stat, distance);
                stat = nStat;
            }
        }
        std::cout << stations.size() << " stations have been imported successfully" << std::endl;
    } else {
        std::cout << "Couldn't open '" << filename << "'" << std::endl;
    }
    file.close();
}

Station* Network::addStation(std::string name, std::string lineName) {
    Station * stat;
    
    try {
        // Check if neighbour already exists
        stat = stations.at(name);
    } catch (std::out_of_range e) {
        stat = new Station(name);
        stations[name] = stat;
    }
    
    stat->addLine(lineName);
    
    return stat;
}

void Network::info() const {
    if(stations.empty()){
        std::cout << "No station exists" << std::endl;
    }else{
        for (auto it = stations.begin(); it != stations.end(); ++it) {
            it->second->info();
        }
    }
}

void Network::help() const{
    //open README.txt
    std::ifstream file("README.txt");
    if(file.is_open()){
        while(!file.eof()){
            std::string line;
            std::getline(file,line);
            std::cout << line << std::endl;
        }
    }else {
        std::cout << "No help found, too bad bruh" << std::endl;
    }
    file.close();
}

Network::~Network() {
    for(auto it = stations.begin(); it != stations.end(); ++ it) {
        delete it->second;
    }
}