#ifndef __gsb__bank__
#define __gsb__bank__

#include <exception>
#include <string>
#include "citizen.h"


class NotFoundCitizen : public std::exception {
 public:
  virtual const char* what() const throw() { return "Not found citizen"; }
};

enum class account_type {CHECKING = 0, SAVING = 1, CURRENCY = 2};
enum class account_parameters {IS = 0, TRANSFER_CHARGE = 1, INTEREST_RATE = 2, MONTHLY_CHARGE = 3};
union parameter_types {
	bool _bool;
	double _double;
};

class Bank {
	public :
		Bank (const std::string& name, parameter_types**);
	
	
}

class BankBuilder {
	private:
		std::string name;	
		
		parameter_types parameters[3][4];		// może trzeba wyzerować 
		/*parameters[account_type::CHECKING][account_parameters::IS]._bool = false;
		parameters[account_type::SAVING][account_parameters::IS]._bool =   false;
		parameters[account_type::CURRENCY][account_parameters::IS]._bool = false;*/
		
		account_type currently_set_type;
	
	public:
		// do ustawiania wartości:
		BankBuilder();
		BankBuilder& name(const std::string name);
		BankBuilder& checkingAccount();
		BankBuilder& savinggAccount();
		BankBuilder& currencyAccount();
		BankBuilder& monthlyCharge(double);
		BankBuilder& transferCharge(double);
		BankBuilder& interestRate(double);
		
		// do tworzenia banku:
		Bank& createBank();
}

class Gkb {
	public:
		BankBuilder& bankApplication() const;
		static Gkb& gkb();
		
	private:
		Gkb(){}
		Gkb( const Gkb & ){}
}
#define gkb() Gkb::gkb()

#endif /* defined(__gsb__bank__) */
