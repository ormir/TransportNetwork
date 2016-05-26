//
//  network.cpp
//  TransportNetwork
//
//  Created by Ormir G. on 26/05/16.
//  Copyright © 2016 Nitika Kumar & Ormir Gjurgjej. All rights reserved.
//

#include "network.hpp"

Network::Network(std::string filename) {
    import(filename);
}

bool Network::path(std::string bName, std::string eName) {
    // find begin and end station
    Station *source, *destination;
    try {
        source = stations.at(bName);
        destination = stations.at(eName);
    } catch (std::out_of_range e) {
        std::cout << "Couldn't find begin or end station" << std::endl;
        return false;
    }
    
    Station * head = source;
    auto cmp = [&](Station* left, Station* right) { return left->getDistance(head) < right->getDistance(head); };
    std::priority_queue<Station*, std::vector<Station*>, decltype(cmp)> queue(cmp);
    queue.push(head);
    
    std::set<Station*> visited;
    std::map<Station*, int> dist;
    std::vector<Station*> prev;
    dist[source] = 0;
    
    while (!queue.empty()) {
        head = queue.top();
        if (head == destination) break;
        queue.pop();
        if (visited.find(head) != visited.end()) continue;
        visited.insert(head);
        
        // Iterate Neighbours
        std::map<Station*, int> nb = head->getNeighbours();
        for (auto it = nb.begin(); it != nb.end(); ++it) {
            // Check if distance already is saved
            auto di = dist.find(it->first);
            
            // Distance update
            int newDis = dist[head] + head->getDistance(it->first);
            
            if (di == dist.end() || newDis < dist[it->first]) {
                dist[it->first] = newDis;
                prev.push_back(it->first);
                queue.push(it->first);
            }
        }
    }
    
    
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
    for (auto it = stations.begin(); it != stations.end(); ++it) {
        it->second->info();
    }
}

Network::~Network() {
    for(auto it = stations.begin(); it != stations.end(); ++ it) {
        delete it->second;
    }
}


//class StationPriority {
//    bool operator()(const Station& lst, const Station& rst) const
//    {
//        return lst. < rhs.age;
//    }
//};