#ifndef __gsb__citizen__
#define __gsb__citizen__
#include <string>

// Wirtualna klasa obywateli:
class Citizen {
	public:
		typedef int id_citizen_t;
		const id_citizen_t id() const;
		const std::string& name() const;
	protected :
		Citizen (const std::string& name);  
	private:
		const id_citizen_t my_id;
		const std::string my_name;
		static id_citizen_t new_id;   // pierwsze wolne id.
};


// Szczególne klasy obywateli:
// Klasa ludzi
class Human: public Citizen {
	public:
		Human (const std::string& name);
};

// Klasa klingonów
class Klingon: public Citizen {
	public:
		Klingon (const std::string& name);
};	

// Klasa binarów
class Binar: public Citizen {
	public:
		Binar (const std::string& name);
};

// Klasa binarów dwu osobowych
class Double_binar: public Citizen {
	public:
		Double_binar (const Binar& b1, const Binar& b2);
};
#endif /* defined(__gsb__citizen__) */