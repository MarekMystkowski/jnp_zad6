#include "citizen.h"
#include <iostream>
#include <assert.h>

using namespace std;

int main() {
	cout << "start testu ludzi" << endl;
	Human jan("jan");
	assert (jan.name() == "jan");
	auto ola = Human( "ola");
	assert (ola.name() == "ola");
	assert (ola.id() != jan.id());
	
	auto b0 = Binar("0");
	auto b1 = Binar("1");
	auto db = Double_binar(b0, b1);
	assert (db.name() == "0&1");
	
	cout << "test ludzi: OK" << endl;
	return 0;
}
