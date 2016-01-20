#ifndef __gsb__planet__
#define __gsb__planet__
#include <map>
#include <exception>
#include <string>
#include "citizen.h"
#include <memory>
#include <iostream>

class NotFoundCitizen : public std::exception {
 public:
  virtual const char* what() const throw() { return "Not found citizen"; }
};

class Planet {
	public:
		const Citizen& findCitizen (Citizen::id_citizen_t id) const;
		
	protected: 
		void register_citizen(const Citizen& citizen);	// Rejestruje w klasie Planet
		Planet ();
		
	private: 
		typedef std::shared_ptr<Citizen> map_value_t;
		std::map<Citizen::id_citizen_t, map_value_t > map_resident;
};


class Earth: public Planet {
	public:
		const Human& registerCitizen (const std::string& name);
		static Earth& earth();
		
	private:
		Earth();
		Earth( const Earth & );
};


class Qonos: public Planet {
	public:
		const Klingon& registerCitizen (const std::string& name);
		static Qonos& qonos();
		
	private:
		Qonos();
		Qonos( const Qonos & );
};


class Bynaus: public Planet{
	public:
		const Binar& registerCitizen (const std::string& name);
		const Double_binar& registerCitizen (const Binar& b1, const Binar& b2);
		static Bynaus& bynaus();
		
	private:
		Bynaus();
		Bynaus( const Bynaus & );
};


#define earth() Earth::earth()
#define qonos() Qonos::qonos()
#define bynaus() Bynaus::bynaus()
#endif /* defined(__gsb__planet__) */
