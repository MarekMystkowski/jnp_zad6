#include "bank.h"
#include <memory>
static Account::id_acc_t new_id = 0;

// pomocnicze funkcje:
static void default_account_parameters(parameter_types par[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                       [NUMBER_OF_PARAMERERS_OF_ACCOUNTS]) {
	for (int i = 0; i < NUMBER_OF_TYPES_OF_ACCOUNTS; i++)
		for (int j = 0; j < NUMBER_OF_PARAMERERS_OF_ACCOUNTS; j++) 
			par[i][j] = 0.0;
}


// Bank
Bank::Bank (const std::string& name,
                const parameter_types par[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                                 [NUMBER_OF_PARAMERERS_OF_ACCOUNTS]
		     ) : bank_name(name) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++) parameters[i][j] = par[i][j];
	
	// Ustawianie domyślnych wartości walut.
	for (int i = 0; i < NUMBER_OF_CURRENCY; i++) {
		table_of_exchange_buying_rates[i] = 1.0;
		table_of_exchange_selling_rates[i] = 1.0;
	}
}

double Bank::transferCharge(account_type type) const {
	return parameters[(int) type][(int) account_parameters::TRANSFER_CHARGE];
}

// Do informacji o aktualnym kursie:
double Bank::exchange_buying_rate (Currency curr) const{
	return table_of_exchange_buying_rates[(int)curr];
}
double Bank::exchange_selling_rate (Currency curr) const{
	return table_of_exchange_selling_rates[(int)curr];
}

// metody do zmieniania kusru walut:
Bank& Bank::exchangeTable() {
	is_fixed_exchange = false;
	return *this;
}

Bank& Bank::exchangeRate(Currency curr) {
	is_fixed_exchange = true;
	currently_set_exchange = curr;
	return *this;
}

Bank& Bank::buyingRate(double v) {
	table_of_exchange_buying_rates[(int)currently_set_exchange] = v;
	return *this;
}

Bank& Bank::sellingRate(double v) {
	table_of_exchange_selling_rates[(int)currently_set_exchange] = v;
	return *this;
}

// Otwieranie konto:
Account& Bank::openCheckingAccount(const Citizen& citizen) const {
	return gkb().create_checking_account(*this, citizen);	
}

Account& Bank::openSavingAccount(const Citizen& citizen) const {
	return gkb().create_saving_account(*this, citizen);	
}

Account& Bank::openCurrencyAccount(const Citizen& citizen, Currency curr) const {
	return gkb().create_currency_account(*this, citizen, curr);	
}

// BankBuilder:
BankBuilder::BankBuilder() {
	default_account_parameters (parameters);
	is_fixed_type = false;
}

BankBuilder& BankBuilder::name(const std::string _name) {
    bank_name = _name;
    return *this;
}

BankBuilder& BankBuilder::checkingAccount() {
    currently_set_type = account_type::CHECKING;
    is_fixed_type = true;
    return *this;
}

BankBuilder& BankBuilder::savingAccount() {
    currently_set_type = account_type::SAVING;
    is_fixed_type = true;
    return *this;
}

BankBuilder& BankBuilder::currencyAccount() {
    currently_set_type = account_type::CURRENCY;
    is_fixed_type = true;
    return *this;
}

BankBuilder& BankBuilder::monthlyCharge(double value) {
	if (not is_fixed_type) return *this;
	parameters[(int)currently_set_type][(int)account_parameters::MONTHLY_CHARGE] = value;
	return *this;
}

BankBuilder& BankBuilder::transferCharge(double value) {
	if (not is_fixed_type) return *this;
	parameters[(int)currently_set_type][(int)account_parameters::TRANSFER_CHARGE] = value;
	return *this;
}

BankBuilder& BankBuilder::interestRate(double value) {
	if (not is_fixed_type) return *this;
	parameters[(int)currently_set_type][(int)account_parameters::INTEREST_RATE] = value;
	return *this;
}

Bank& BankBuilder::createBank() const {
	Bank bank = Bank(bank_name, parameters);
	return *std::make_shared<Bank> (bank);
}


// Konta:
Account::Account (const Bank& my_bank, const Citizen& citi, Currency curr)
	: bank(my_bank), citizen(citi), currency(curr), my_balance(0.0), my_id(new_id++) {}

Account::id_acc_t Account::id() const {
	return my_id;
}

double Account::transferCharge() const {
	return 0.0;
}

void Account::deposit(double amount) {
	my_balance += amount;
}

void Account::withdraw(double amount) {
	if (amount > my_balance ) throw "za malo kasy";
	my_balance -= amount;
}

void Account::transfer(double amount, Account::id_acc_t recipient, const std::string& title) {
	if (not gkb().is_account(recipient)) throw "Nie ma konta";	
	if (amount > my_balance - transferCharge() ) throw "za malo kasy";															// Mądrzejszy wyjątek
	my_balance -= amount + transferCharge();
	auto& reci = gkb().find_account(recipient);
	double payment = amount; // wpłąta u adresata
	if (currency != reci.currency) {
		// Przewalutowanie:
		if (currency != Currency::ENC) {
			payment *= bank.exchange_selling_rate(currency);
		}
		if (reci.currency != Currency::ENC) {
			payment /= reci.bank.exchange_buying_rate(currency);
		}
	}
	
	reci.my_balance += payment;
	
	// Zarejestrowanie w histori.																					// Napisać
	
} 


// CheckingAccount:
CheckingAccount::CheckingAccount(const Bank& my_bank, const Citizen& citizen) :
                 Account (my_bank, citizen, Currency::ENC){}

double CheckingAccount::transferCharge() const {
	return bank.transferCharge(account_type::CHECKING);
}

// SavingAccount:
SavingAccount::SavingAccount(const Bank& my_bank, const Citizen& citizen) :
                 Account (my_bank, citizen, Currency::ENC){}

double SavingAccount::transferCharge() const {
	return bank.transferCharge(account_type::SAVING);
}

// CurrencyAccount:
CurrencyAccount::CurrencyAccount(const Bank& my_bank, const Citizen& citizen,Currency curr) :
                 Account (my_bank, citizen, curr){}

double CurrencyAccount::transferCharge() const {
	return bank.transferCharge(account_type::CURRENCY);
}


// Gkb:
BankBuilder& Gkb::bankApplication() const {
	BankBuilder bank_builder;
	return *std::make_shared<BankBuilder> (bank_builder);	
}

Gkb& Gkb::gkb() {
	static Gkb _gkb;
	return _gkb;
}

bool Gkb::is_account(Account::id_acc_t id) {
	return (map_account.count(id) != 0);
}

Account& Gkb::find_account(Account::id_acc_t id) {
	if (map_account.count(id) == 0) throw "nie ma konta o tym id";					 // bardziej sensowny wyjątek stworzyć.
	return *map_account.at(id);
}

Account& Gkb::create_checking_account(const Bank& bank, const Citizen& citizen) {
	CheckingAccount _checking_account(bank, citizen);
	auto shar = std::make_shared<Account> (_checking_account);
	map_account[_checking_account.id()] = shar;
	return *shar;
}

Account& Gkb::create_saving_account(const Bank& bank, const Citizen& citizen) {
	SavingAccount _saving_account(bank, citizen);
	auto shar = std::make_shared<Account> (_saving_account);
	map_account[_saving_account.id()] = shar;
	return *shar;
}

Account& Gkb::create_currency_account(const Bank& bank, const Citizen& citizen, Currency curr){
	CurrencyAccount _currency_account(bank, citizen, curr);
	auto shar = std::make_shared<Account> (_currency_account);
	map_account[_currency_account.id()] = shar;
	return *shar;
}
