#include "planet.h"


// Planet:
template<typename Resident_t>
Planet<Resident_t>::Planet() : map_resident() {}

template<typename Resident_t>
const Resident_t&  Planet<Resident_t>::register_citizen (const Resident_t& citizen) {
	Resident_t _citizen = citizen;
	auto shar_cit = std::make_shared<Resident_t>(_citizen);
	map_resident[citizen.id()] = shar_cit;
	return *shar_cit;
}


// Earth:
Earth::Earth() : Planet<Human>() {}
			
const Human& Earth::registerCitizen (const std::string& name) {
	return register_citizen ( Human (name) );		// rejestracja w nadklasie.
}

Earth& Earth::earth() {
	static Earth _earth;
	return _earth;
}


// Qonos:
Qonos::Qonos() : Planet<Klingon>() {}

const Klingon& Qonos::registerCitizen (const std::string& name) {
	return register_citizen ( Klingon (name) );		// rejestracja w nadklasie.
}

Qonos& Qonos::qonos() {
	static Qonos _qonos;
	return _qonos;
}

// Bynaus:
Bynaus::Bynaus() : Planet<Binar>() {}

const Binar& Bynaus::registerCitizen (const std::string& name) {
	return register_citizen ( Binar (name) );		// rejestracja w nadklasie.
}

Bynaus& Bynaus::bynaus() {
	static Bynaus _bynaus;
	return _bynaus;
}

