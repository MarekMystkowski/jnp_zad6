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
		virtual Citizen& findCitizen (Citizen::id_citizen_t id) const;
		
	protected: 
	//	void register_citizen(const Citizen& citizen);	// Rejestruje w klasie Planet
		Planet ();
		
//	private: 
//		typedef std::shared_ptr<Citizen> map_value_t;
//		std::map<Citizen::id_citizen_t, map_value_t > map_resident;
};


class Earth: public Planet {
	public:
		Human& registerCitizen (const std::string& name);
		static Earth& earth();
		virtual Human& findCitizen (Citizen::id_citizen_t id) const;
		
	private:
		Earth();
		Earth( const Earth & );
		std::map<Citizen::id_citizen_t, std::shared_ptr<Human> > map_resident;
};


class Qonos: public Planet {
	public:
		Klingon& registerCitizen (const std::string& name);
		static Qonos& qonos();
		virtual Klingon& findCitizen (Citizen::id_citizen_t id) const;
		
	private:
		Qonos();
		Qonos( const Qonos & );
		std::map<Citizen::id_citizen_t, std::shared_ptr<Klingon> > map_resident;
};


class Bynaus: public Planet{
	public:
		Binar& registerCitizen (const std::string& name);
		Binar& registerCitizen (const Binar& b1, const Binar& b2);
		static Bynaus& bynaus();
		virtual Binar& findCitizen (Citizen::id_citizen_t id) const;
		
	private:
		Bynaus();
		Bynaus( const Bynaus & );
		std::map<Citizen::id_citizen_t, std::shared_ptr<Binar> > map_resident;
};


#define earth() Earth::earth()
#define qonos() Qonos::qonos()
#define bynaus() Bynaus::bynaus()
#endif /* defined(__gsb__planet__) */
