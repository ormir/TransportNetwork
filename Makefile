main: main.o network.o station.o
		g++ -std=c++11 main.o network.o station.o -o TransportNetwork

main.o: main.cpp
		g++ -std=c++11 -c main.cpp

network.o: network.cpp network.hpp
		g++ -std=c++11 -c network.cpp

station.o: station.cpp station.hpp
		g++ -std=c++11 -c station.cpp

start: main
		./TransportNetwork ubahn.txt README.txt

clean: 
		rm *.o TransportNetwork