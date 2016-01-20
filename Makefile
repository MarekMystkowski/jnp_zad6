all: test_ludzi

citizen.o: citizen.cc citizen.h
	g++ -Wall -std=c++11 citizen.cc -c -o citizen.o
planet.o: planet.cc planet.h
	g++ -Wall -std=c++11 planet.cc -c -o planet.o

test_planet.o: test_planet.cpp planet.h
	g++ -Wall -std=c++11 test_planet.cpp -c -o test_planet.o
test_planet: test_planet.o planet.o citizen.o
	g++ test_planet.o planet.o citizen.o -o test_planet

test_ludzi.o: test_ludzi.cpp citizen.h
	g++ -Wall -std=c++11 test_ludzi.cpp -c -o test_ludzi.o
test_ludzi: test_ludzi.o citizen.o 
	g++ test_ludzi.o citizen.o -o test_ludzi

rm:
	rm citizen.o test_ludzi.o test_ludzi planet.o test_planet.o test_planet
