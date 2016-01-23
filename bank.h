#ifndef __gsb__bank__
#define __gsb__bank__

#include <exception>
#include <string>
#include <map>
#include <memory>
#include <initializer_list>
#include <tuple>
#include "citizen.h"
#include <iostream>
#include "interstellarclock.h"

// Waluty:
#define  NUMBER_OF_CURRENCY 4
enum class Currency { ENC = 0, BIC = 1, DIL = 2, LIT = 3 };

// Wyjątki:
class NegativeBalance : public std::exception {
 public:
  virtual const char* what() const throw() { return "Negative balance!"; }
};

class NotEnoughMoney : public std::exception {
 public:
  virtual const char* what() const throw() { return "Not enough money!"; }
};

class WrongTypeOfCurrency : public std::exception {
 public:
  virtual const char* what() const throw() { return "Wrong type of currency!"; }
};

class NoAccountFound : public std::exception {
 public:
  virtual const char* what() const throw() { return "No account found!"; }
};

class NegativeAmount : public std::exception {
 public:
  virtual const char* what() const throw() { return "Negative amount!"; }
};



class CheckingAccount;
class SavingAccount;
class CurrencyAccount;
class Account;

class ExchangeTable {
	public: 
		ExchangeTable();
		ExchangeTable& exchangeRate(Currency curr);
        ExchangeTable& buyingRate(double);
        ExchangeTable& sellingRate(double);
        double exchange_buying_rate (Currency curr) const;
		double exchange_selling_rate (Currency curr) const;
		

	private:
		double tab_selling_rates[NUMBER_OF_CURRENCY];
		double tab_buying_rates[NUMBER_OF_CURRENCY];
		Currency currently_set_exchange;
		bool is_fixed_exchange;
};

class ParametersBank {
	public :
		ParametersBank();
		//ParametersBank& operator= (const ParametersBank& data);
		static const int nummber_of_types = 3;
		static const int number_of_parameters = 3;
		
		enum class AccountType : int {CHECKING = 0, SAVING = 1, CURRENCY = 2};
		enum class AccountParameters : int {TRANSFER_CHARGE = 0, INTEREST_RATE = 1, MONTHLY_CHARGE = 2};
		typedef double parameter_types ;
		parameter_types getParameters (AccountType, AccountParameters) const;
		void setParameters (AccountType, AccountParameters, parameter_types);
	private:
		parameter_types parameters[nummber_of_types][number_of_parameters];
	
};

class Bank {
	public :
		Bank (const std::string& name, std::shared_ptr<ParametersBank> parameters);
		
		// Otwieranie kont:
		CheckingAccount& openCheckingAccount(const Citizen& citizen) const;
		SavingAccount& openSavingAccount(const Citizen& citizen) const;	
		CurrencyAccount& openCurrencyAccount(const Citizen& citizen, Currency curr) const;
		
		// Zwraca opłąty naliczane przez bank
		double transferCharge(ParametersBank::AccountType) const;
		double interestRate(ParametersBank::AccountType) const;
		double monthlyCharge(ParametersBank::AccountType) const;

		
		// Zwracanie kursu waluty do ENC:
		double exchange_buying_rate (Currency curr) const;
		double exchange_selling_rate (Currency curr) const;
		
		ExchangeTable& exchangeTable();
        		
	private:
		std::string bank_name;
		std::shared_ptr<ParametersBank> parameters;
		ExchangeTable * my_exchange_tabl;
};

class BankBuilder {
	private:
		std::string bank_name;	
	
		std::shared_ptr<ParametersBank> parameters;
		ParametersBank::AccountType currently_set_type;
		bool is_fixed_type;
	
	public:
		// do ustawiania wartości:
		BankBuilder(std::shared_ptr<ParametersBank> parameters);
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
		std::string balance() const;
		const std::string& history() const;
		virtual void deposit(double);
		virtual void withdraw(double);
		virtual void deposit(struct payment_format);
		virtual void withdraw(struct payment_format);
		void notify();
		
		friend std::ostream& operator<<(std::ostream& os, const Account& acc);
		
		
	protected:
		Account (const Bank& my_bank, const Citizen& citizen, Currency curr );
		std::string my_history;
		const Bank& bank;
		virtual double transferCharge() const;
		virtual double interestRate() const;
		virtual double monthlyCharge() const;
		Currency currency;
		double my_balance;
		
	private:
		const Citizen& citizen;
		const id_acc_t my_id;
		
};

class CheckingAccount : public Account {
	public:
		CheckingAccount(const Bank& my_bank, const Citizen& citizen);
		virtual void withdraw(double x) {Account::withdraw(x);}
		virtual void deposit(double x) {Account::deposit(x);}
		virtual void withdraw(struct payment_format x) {Account::withdraw(x);}
		virtual void deposit(struct payment_format x) {Account::deposit(x);}
		
	private: 
		virtual double transferCharge() const;
		virtual double interestRate() const;
		virtual double monthlyCharge() const;
};

class SavingAccount : public Account {
	public:
		SavingAccount(const Bank& my_bank, const Citizen& citizen);
	private:
		virtual double transferCharge() const;
		virtual double interestRate() const;
		virtual double monthlyCharge() const;
		virtual void deposit(double){}
		virtual void withdraw(double){}
		virtual void deposit(struct payment_format){}
		virtual void withdraw(struct payment_format){}

};

class CurrencyAccount : public Account {
	public:
		CurrencyAccount(const Bank& my_bank, const Citizen& citizen, Currency curr);
		virtual void withdraw(double x) {Account::withdraw(x);}
		virtual void deposit(double x) {Account::deposit(x);}
		virtual void deposit(struct payment_format);
		virtual void withdraw(struct payment_format);
	
	private:
		virtual double transferCharge() const;
		virtual double interestRate() const;
		virtual double monthlyCharge() const;
};

class Gkb {
	public:
		BankBuilder& bankApplication();
		Bank& createBank(const std::string& name, std::shared_ptr<ParametersBank> parameters);
		static Gkb& gkb();
		bool is_account(Account::id_acc_t);									
		Account& find_account(Account::id_acc_t);
		
		// Do tworzenia kont:
		CheckingAccount& create_checking_account(const Bank& bank, const Citizen& citizen);
		SavingAccount& create_saving_account(const Bank& bank, const Citizen& citizen);
		CurrencyAccount& create_currency_account(const Bank& bank, const Citizen& citizen, Currency curr);
		
	private:
		Gkb(){}
		Gkb( const Gkb & ){}
		
		// do trzymania wszystkich kont:
		std::map<Account::id_acc_t, std::shared_ptr<CheckingAccount> > map_checking_account;
		std::map<Account::id_acc_t, std::shared_ptr<SavingAccount> > map_saving_account;
		std::map<Account::id_acc_t, std::shared_ptr<CurrencyAccount> > map_currency_account;
		
		// mapa dla banków:
		std::map<int, std::shared_ptr<Bank> > map_bank;
		std::map<int, std::shared_ptr<ParametersBank> > map_parameters_bank;
};
#define gkb() Gkb::gkb()


#endif /* defined(__gsb__bank__) */
