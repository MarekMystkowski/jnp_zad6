#include "citizen.h"

// Citizen:
Citizen::id_citizen_t Citizen::new_id = 0;

Citizen::Citizen (const std::string& name) : my_id (new_id++), my_name (name) {}; 

const Citizen::id_citizen_t Citizen::id() const {
	return my_id;
}

const std::string& Citizen::name() const {
	return my_name;
}

// Human
Human::Human (const std::string& name) : Citizen (name) {};

// Klingon
Klingon::Klingon (const std::string& name) : Citizen (name) {};

// Binar
Binar::Binar (const std::string& name) : Citizen (name) {};

// Double Binar
Binar::Binar (const Binar& b1, const Binar& b2) :
		Citizen (b1.name() + "&" + b2.name()) {};

