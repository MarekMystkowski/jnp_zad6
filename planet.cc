#include "planet.h"


// Planet:
Planet::Planet() : map_resident() {}

void Planet::register_citizen (const Citizen& citizen) {
	Citizen _citizen = citizen; 
	map_resident[citizen.id()] = std::make_shared<Citizen> (_citizen);
}

const Citizen& Planet::findCitizen (Citizen::id_citizen_t id) const {
	if (map_resident.count(id) == 0) throw NotFoundCitizen();  // bardziej sensowny wyjątek stworzyć.
	return *map_resident.at(id);
}


// Earth:
Earth::Earth() : Planet() {}
			
const Human& Earth::registerCitizen (const std::string& name) {
	auto shar_human = std::make_shared<Human> (Human(name));
	register_citizen ( *shar_human );		// rejestracja w nadklasie.
	return *shar_human;
}

Earth& Earth::earth() {
	static Earth _earth;
	return _earth;
}

// Qonos:
Qonos::Qonos() : Planet() {}

const Klingon& Qonos::registerCitizen (const std::string& name) {
	auto shar_kling = std::make_shared<Klingon> (Klingon(name));
	register_citizen ( *shar_kling );		// rejestracja w nadklasie.
	return *shar_kling;
}

Qonos& Qonos::qonos() {
	static Qonos _qonos;
	return _qonos;
}


// Bynaus:
Bynaus::Bynaus() : Planet() {}

const Binar& Bynaus::registerCitizen (const std::string& name) {
	auto binar = Binar(name);
	auto shar_binar = std::make_shared<Binar> (binar);
	register_citizen ( *shar_binar );		// rejestracja w nadklasie.
	
	auto binar2 (binar);
	return *std::make_shared<Binar> (binar2);
}

const Double_binar& Bynaus::registerCitizen (const Binar& b1, const Binar& b2) {
	auto duble_binar = Double_binar(b1, b2);
	register_citizen ( duble_binar );		// rejestracja w nadklasie.
	return * std::make_shared<Double_binar> (duble_binar);
}

Bynaus& Bynaus::bynaus() {
	static Bynaus _bynaus;
	return _bynaus;
}

