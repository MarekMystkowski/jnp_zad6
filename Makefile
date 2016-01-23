all: observe.o citizen.o citizen.o bank.o interstellarclock.o planet.o

citizen.o: citizen.cc citizen.h
	g++ -Wall -std=c++11 citizen.cc -c -o citizen.o
planet.o: planet.cc planet.h
	g++ -Wall -std=c++11 planet.cc -c -o planet.o
bank.o: bank.cc bank.h
	g++ -Wall -std=c++11 bank.cc -c -o bank.o
observe.o: observe.cc observe.h
	g++ -Wall -std=c++11 observe.cc -c -o observe.o

interstellarclock.o: interstellarclock.cpp interstellarclock.h
	g++ -Wall -std=c++11 interstellarclock.cpp -c -o interstellarclock.o

test: all gsb_example
	./gsb_example

gsb_example.o: gsb_example.cpp gsb.h
	g++ -Wall -std=c++11 gsb_example.cpp -c -o gsb_example.o

gsb_example: gsb_example.o observe.o citizen.o citizen.o bank.o interstellarclock.o planet.o
	g++ gsb_example.o observe.o citizen.o bank.o interstellarclock.o planet.o -o gsb_example



rm:
	rm observe.o citizen.o bank.o interstellarclock.o planet.o
rm_all:
	make rm
	rm gsb_example gsb_example.o
