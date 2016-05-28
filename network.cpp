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
    
    auto cmp = [](std::pair<int, Station*> left, std::pair<int, Station*> right) {
        return left.first > right.first;
    };
    
    std::priority_queue<std::pair<int, Station*>, std::vector<std::pair<int, Station*>>, decltype(cmp)> queue(cmp);
    queue.push(std::make_pair(0, source));
    
    std::set<Station*> visited;
    std::map<Station*, int> dist;
    dist[source] = 0;
    
    while (!queue.empty()) {
        head = queue.top().second;
        if (head == destination) break;
        queue.pop();
        if (visited.find(head) != visited.end()) continue;
        visited.insert(head);
        
        // Iterate Neighbours
        std::map<Station*, int> nbList = head->getNeighbours();
        for (auto nb = nbList.begin(); nb != nbList.end(); ++nb) {
            // Check if distance already is saved
            auto dis = dist.find(nb->first);
            
            // Distance update
            int newDis = dist[head] + head->getDistance(nb->first);
            
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
            if (nbShort == nullptr) nbShort = nb->first;
            else if (visited.find(nb->first) != visited.end() &&
                     dist[nbShort] > dist[nb->first]) {
                nbShort = nb->first;
            }
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