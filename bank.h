#ifndef __gsb__bank__
#define __gsb__bank__

#include <exception>
#include <string>
#include "citizen.h"

#define  NUMBER_OF_TYPES_OF_ACCOUNTS 3
#define  NUMBER_OF_PARAMERERS_OF_ACCOUNTS 3
enum class account_type : int {CHECKING = 0, SAVING = 1, CURRENCY = 2};
enum class account_parameters : int {TRANSFER_CHARGE = 0, INTEREST_RATE = 1, MONTHLY_CHARGE = 2};
typedef double parameter_types ;


class IncorrectBuildingBank : public std::exception {
 public:
  virtual const char* what() const throw() { return "Incorrect building bank"; }
};

class Bank {
	public :
		Bank (const std::string& name, parameter_types const 
				par[NUMBER_OF_TYPES_OF_ACCOUNTS][NUMBER_OF_PARAMERERS_OF_ACCOUNTS]);
		
	
	private:
		std::string bank_name;
		parameter_types parameters[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                                 [NUMBER_OF_PARAMERERS_OF_ACCOUNTS];
	
};

class BankBuilder {
	private:
		std::string bank_name;	
		
		parameter_types parameters[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                                 [NUMBER_OF_PARAMERERS_OF_ACCOUNTS];
		
		account_type currently_set_type;
	
	public:
		// do ustawiania wartości:
		BankBuilder();
		BankBuilder& name(const std::string);
		BankBuilder& checkingAccount();
		BankBuilder& savingAccount();
		BankBuilder& currencyAccount();
		BankBuilder& monthlyCharge(double);
		BankBuilder& transferCharge(double);
		BankBuilder& interestRate(double);
		
		// do tworzenia banku:
		Bank& createBank() const;
};

class Gkb {
	public:
		BankBuilder& bankApplication() const;
		static Gkb& gkb();
		
	private:
		Gkb(){}
		Gkb( const Gkb & ){}
};
#define gkb() Gkb::gkb()

#endif /* defined(__gsb__bank__) */
