#include "planet.h"
#include <iostream>
#include <assert.h>

using namespace std;
int main() {

	auto jan = earth().registerCitizen("Jan");
	auto ala = earth().registerCitizen("Ala");
	auto x = earth().findCitizen(jan.id());
	assert(earth().findCitizen(jan.id()).name() == earth().findCitizen(jan.id()).name() );
	
	cout << "test ok." << endl;
	return 0;
}
