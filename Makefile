test:  test_ludzi test_planet test_bank
	./test_ludzi 
	./test_planet 
	./test_bank
all: test_ludzi test_planet test_bank

citizen.o: citizen.cc citizen.h
	clang++-3.7 -g -Wall -std=c++11 citizen.cc -c -o citizen.o
planet.o: planet.cc planet.h
	clang++-3.7 -g -Wall -std=c++11 planet.cc -c -o planet.o
bank.o: bank.cc bank.h
	clang++-3.7 -g -Wall -std=c++11 bank.cc -c -o bank.o

test_planet.o: test_planet.cpp planet.h
	clang++-3.7 -g -Wall -std=c++11 test_planet.cpp -c -o test_planet.o
test_planet: test_planet.o planet.o citizen.o
	clang++-3.7 test_planet.o planet.o citizen.o -o test_planet

test_ludzi.o: test_ludzi.cpp citizen.h
	clang++-3.7 -g -Wall -std=c++11 test_ludzi.cpp -c -o test_ludzi.o
test_ludzi: test_ludzi.o citizen.o 
	clang++-3.7 test_ludzi.o citizen.o -o test_ludzi

test_bank.o: test_bank.cpp bank.h
	clang++-3.7 -g -Wall -std=c++11 test_bank.cpp -c -o test_bank.o
test_bank: test_bank.o citizen.o planet.o bank.o interstellarclock.o
	clang++-3.7 test_bank.o citizen.o planet.o bank.o interstellarclock.o -o test_bank

interstellarclock.o: interstellarclock.cpp interstellarclock.h
	clang++-3.7 -g -Wall -std=c++11 interstellarclock.cpp -c -o interstellarclock.o

gsb_test01.o: gsb_test01.cpp 
	clang++-3.7 -g -Wall -std=c++11 gsb_test01.cpp -c -o gsb_test01.o
gsb_test01: gsb_test01.o citizen.o planet.o bank.o interstellarclock.o
	clang++-3.7 gsb_test01.o citizen.o planet.o bank.o interstellarclock.o -o gsb_test01

gsb_test02.o: gsb_test02.cpp 
	clang++-3.7 -g -Wall -std=c++11 gsb_test02.cpp -c -o gsb_test02.o
gsb_test02: gsb_test02.o citizen.o planet.o bank.o interstellarclock.o
	clang++-3.7 gsb_test02.o citizen.o planet.o bank.o interstellarclock.o -o gsb_test02

rm:
	rm citizen.o test_ludzi.o test_ludzi planet.o test_planet.o test_planet bank.o test_bank.o test_bank interstellarclock.o
