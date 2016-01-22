#include "planet.h"


// Planet:
Planet::Planet() {}

Citizen& Planet::findCitizen (Citizen::id_citizen_t id) const {
	throw NotFoundCitizen();  // bardziej sensowny wyjątek stworzyć.
}


// Earth:
Earth::Earth() : Planet(), map_resident() {}
			
Human& Earth::registerCitizen (const std::string& name) {
	auto sha_human = std::make_shared<Human> (Human(name));
	map_resident[sha_human->id()] = sha_human;
	return *map_resident.at(sha_human->id());
}

Earth& Earth::earth() {
	static Earth _earth;
	return _earth;
}

Human& Earth::findCitizen (Citizen::id_citizen_t id) const {
	return *map_resident.at(id);
}

// Qonos:
Qonos::Qonos() : Planet(), map_resident()  {}

Klingon& Qonos::registerCitizen (const std::string& name) {
	auto sha_klingon = std::make_shared<Klingon> (Klingon(name));
	map_resident[sha_klingon->id()] = sha_klingon;
	return *map_resident.at(sha_klingon->id());
}

Qonos& Qonos::qonos() {
	static Qonos _qonos;
	return _qonos;
}

Klingon& Qonos::findCitizen (Citizen::id_citizen_t id) const {
	return *map_resident.at(id);
}

// Bynaus:
Bynaus::Bynaus() : Planet(), map_resident()  {}

Binar& Bynaus::registerCitizen (const std::string& name) {
	auto sha_binar = std::make_shared<Binar> (Binar(name));
	map_resident[sha_binar->id()] = sha_binar;
	return *map_resident.at(sha_binar->id()) ;
}

Binar& Bynaus::registerCitizen (const Binar& b1, const Binar& b2) {
	auto sha_binar = std::make_shared<Binar> (Binar(b1, b2));
	map_resident[sha_binar->id()] = sha_binar;
	return *map_resident.at(sha_binar->id()) ;
}

Binar& Bynaus::findCitizen (Citizen::id_citizen_t id) const {
	return *map_resident.at(id);
}

Bynaus& Bynaus::bynaus() {
	static Bynaus _bynaus;
	return _bynaus;
}

