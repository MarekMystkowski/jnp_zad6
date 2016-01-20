#ifndef __gsb__planet__
#define __gsb__planet__
#include <map>
#include <exception>
#include <string>
#include "citizen.h"
#include <memory>


template<typename Resident_t>			// typ mieszkańców zamieszkujących planetę
class Planet {
	public:
		const Resident_t& findCitizen (Citizen::id_citizen_t id) const {
			if (map_resident.count(id) == 0) throw "nie ma takiej istoty";  // bardziej sensowny wyjątek stworzyć.
			return *map_resident.at(id);
		}
	
	protected: 
		const Resident_t& register_citizen(const Resident_t& citizen);	// Rejestruje w klasie Planet
		Planet ();
		
	private: 
		typedef std::shared_ptr<Resident_t> map_value_t;
		std::map<Citizen::id_citizen_t, map_value_t > map_resident;
};


class Earth: public Planet<Human> {
	public:
		const Human& registerCitizen (const std::string& name);
		static Earth& earth();
		
	private:
		Earth();
		Earth( const Earth & );
};


class Qonos: public Planet<Klingon> {
	public:
		const Klingon& registerCitizen (const std::string& name);
		static Qonos& qonos();
		
	private:
		Qonos();
		Qonos( const Qonos & );
};


class Bynaus: public Planet<Binar> {
	public:
		const Binar& registerCitizen (const std::string& name);
		static Bynaus& bynaus();
		
	private:
		Bynaus();
		Bynaus( const Bynaus & );
};


#define earth() Earth::earth()
#define qonos() Qonos::qonos()
#define bynaus() Bynaus::bynaus()
#endif /* defined(__gsb__planet__) */
