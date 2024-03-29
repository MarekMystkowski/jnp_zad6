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
	auto db = Binar(b0, b1);
	assert (db.name() == "0&1");
	
	auto db3 = Binar(b0,db);
	assert (db3.name() == "0&0&1");
	
	auto db6 = Binar(db3,db3);
	assert (db6.name() == "0&0&1&0&0&1");

	cout << "test ludzi: OK" << endl;
	return 0;
}
