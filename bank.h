#ifndef __gsb__bank__
#define __gsb__bank__

#include <exception>
#include <string>
#include <map>
#include <memory>
#include <initializer_list>
#include <tuple>
#include "citizen.h"


#define  NUMBER_OF_TYPES_OF_ACCOUNTS 3
#define  NUMBER_OF_PARAMERERS_OF_ACCOUNTS 3
#define  NUMBER_OF_CURRENCY 4
enum class account_type : int {CHECKING = 0, SAVING = 1, CURRENCY = 2};
enum class account_parameters : int {TRANSFER_CHARGE = 0, INTEREST_RATE = 1, MONTHLY_CHARGE = 2};
typedef double parameter_types ;

// Waluty:
enum class Currency { ENC = 0, BIC = 1, DIL = 2, LIT = 3 };


class CheckingAccount;
class Account;

class Bank {
	public :
		Bank (const std::string& name, parameter_types const 
				par[NUMBER_OF_TYPES_OF_ACCOUNTS][NUMBER_OF_PARAMERERS_OF_ACCOUNTS]);
		
		// Otwieranie kont:
		Account& openCheckingAccount(const Citizen& citizen) const;
		Account& openSavingAccount(const Citizen& citizen) const;	
		Account& openCurrencyAccount(const Citizen& citizen, Currency curr) const;
		
		// Zwraca opłąty naliczane przez bank
		double transferCharge(account_type) const;
		
		// Zwracanie kursu waluty do ENC:
		double exchange_buying_rate (Currency curr) const;
		double exchange_selling_rate (Currency curr) const;
		
		// Do edycji tabeli kursów:
		Bank& exchangeTable();
        Bank& exchangeRate(Currency curr);
        Bank& buyingRate(double);
        Bank& sellingRate(double);
		
	private:
		std::string bank_name;
		parameter_types parameters[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                                 [NUMBER_OF_PARAMERERS_OF_ACCOUNTS];
		
		double table_of_exchange_selling_rates[NUMBER_OF_CURRENCY];
		double table_of_exchange_buying_rates[NUMBER_OF_CURRENCY];
		
		// Do ustalania nowych wartości:
		Currency currently_set_exchange;
		bool is_fixed_exchange;
};

class BankBuilder {
	private:
		std::string bank_name;	
		
		parameter_types parameters[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                                 [NUMBER_OF_PARAMERERS_OF_ACCOUNTS];
		
		account_type currently_set_type;
		bool is_fixed_type;
	
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

struct payment_format {
	double amount;
	Currency curr;
};
// Klasy związane z kontami:
class Account {
	public:
		typedef int id_acc_t;
		id_acc_t id() const;
		virtual void transfer(double, id_acc_t, const std::string& title); 
		virtual void transfer(double a, id_acc_t);
		std::string& balance() const;
		const std::string& history() const;
		virtual void deposit(double);
		virtual void withdraw(double);
		virtual void deposit(struct payment_format);
		virtual void withdraw(struct payment_format);
		
		
	protected:
		Account (const Bank& my_bank, const Citizen& citizen, Currency curr );
		std::string my_history;
		virtual double transferCharge() const;
		const Bank& bank;
		Currency currency;
		
	private:
		const Citizen& citizen;
		double my_balance;
		id_acc_t my_id;
		
};

class CheckingAccount : public Account {
	public:
		CheckingAccount(const Bank& my_bank, const Citizen& citizen);
		virtual double transferCharge() const;
};

class SavingAccount : public Account {
	public:
		SavingAccount(const Bank& my_bank, const Citizen& citizen);
		virtual double transferCharge() const;
	private:
		virtual void deposit(double){}
		virtual void withdraw(double){}
		virtual void deposit(struct payment_format){}
		virtual void withdraw(struct payment_format){}

};

class CurrencyAccount : public Account {
	public:
		CurrencyAccount(const Bank& my_bank, const Citizen& citizen, Currency curr);
		virtual double transferCharge() const;
		virtual void deposit(struct payment_format);
		virtual void withdraw(struct payment_format);
};

class Gkb {
	public:
		BankBuilder& bankApplication() const;
		static Gkb& gkb();
		bool is_account(Account::id_acc_t);									
		Account& find_account(Account::id_acc_t);
		
		// Do tworzenia kont:
		Account& create_checking_account(const Bank& bank, const Citizen& citizen);
		Account& create_saving_account(const Bank& bank, const Citizen& citizen);
		Account& create_currency_account(const Bank& bank, const Citizen& citizen, Currency curr);
		
	private:
		Gkb(){}
		Gkb( const Gkb & ){}
		
		// do trzymania wszystkich kont:
		std::map<Account::id_acc_t, std::shared_ptr<Account> > map_account;
};
#define gkb() Gkb::gkb()


#endif /* defined(__gsb__bank__) */
