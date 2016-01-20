#include "planet.h"
#include <iostream>
#include <assert.h>

using namespace std;
int main() {

	auto jan = earth().registerCitizen("Jan");
	auto ala = earth().registerCitizen("Ala");
	auto x = earth().findCitizen(jan.id());
	assert(earth().findCitizen(jan.id()).name() == earth().findCitizen(jan.id()).name() );
	
	
	auto& captain = earth().registerCitizen("Jean-Luc Picard");
    auto& officer = qonos().registerCitizen("Worf");
    auto& b0 = bynaus().registerCitizen("00000000");
    auto& b1 = bynaus().registerCitizen("11111111");
    
    auto db = Double_binar(b0, b1);
    auto& binarius = bynaus().registerCitizen(b0, b1);
	cout << "test ok." << endl;
	return 0;
}
