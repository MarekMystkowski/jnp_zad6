test:  test_ludzi test_planet test_bank
	./test_ludzi 
	./test_planet 
	./test_bank
all: test_ludzi test_planet test_bank

citizen.o: citizen.cc citizen.h
	g++ -Wall -std=c++11 citizen.cc -c -o citizen.o
planet.o: planet.cc planet.h
	g++ -Wall -std=c++11 planet.cc -c -o planet.o
bank.o: bank.cc bank.h
	g++ -Wall -std=c++11 bank.cc -c -o bank.o

test_planet.o: test_planet.cpp planet.h
	g++ -Wall -std=c++11 test_planet.cpp -c -o test_planet.o
test_planet: test_planet.o planet.o citizen.o
	g++ test_planet.o planet.o citizen.o -o test_planet

test_ludzi.o: test_ludzi.cpp citizen.h
	g++ -Wall -std=c++11 test_ludzi.cpp -c -o test_ludzi.o
test_ludzi: test_ludzi.o citizen.o 
	g++ test_ludzi.o citizen.o -o test_ludzi

test_bank.o: test_bank.cpp bank.h
	g++ -Wall -std=c++11 test_bank.cpp -c -o test_bank.o
test_bank: test_bank.o citizen.o planet.o bank.o
	g++ test_bank.o citizen.o planet.o bank.o -o test_bank

rm:
	rm citizen.o test_ludzi.o test_ludzi planet.o test_planet.o test_planet bank.o test_bank.o test_bank
