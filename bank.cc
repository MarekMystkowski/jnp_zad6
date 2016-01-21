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

std::string name_currency (Currency curr) {
	std::string s;
	switch(curr) {
		case Currency::ENC:
			s = "ENC";
			break;
		case Currency::BIC:
			s = "BIC";
			break;
		case Currency::DIL:
			s = "DIL";
			break;
		case Currency::LIT:
			s = "LIT";
			break;
	}
	return s;
}

// Bank
Bank::Bank (const std::string& name,
                const parameter_types par[NUMBER_OF_TYPES_OF_ACCOUNTS]
		                                 [NUMBER_OF_PARAMERERS_OF_ACCOUNTS]
		     ) : bank_name(name) {
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++) parameters[i][j] = par[i][j];
	
}

double Bank::transferCharge(account_type type) const {
	return parameters[(int) type][(int) account_parameters::TRANSFER_CHARGE];
}

// Do informacji o aktualnym kursie:
double Bank::exchange_buying_rate (Currency curr) const{
	return my_exchange_tabl.exchange_buying_rate (curr);
}
double Bank::exchange_selling_rate (Currency curr) const{
	return my_exchange_tabl.exchange_selling_rate (curr);
}

// metody do zmieniania kusru walut:
ExchangeTable& Bank::exchangeTable() {
	return my_exchange_tabl;
}

ExchangeTable::ExchangeTable() {
	// Ustawianie domyślnych wartości walut.
	for (int i = 0; i < NUMBER_OF_CURRENCY; i++) {
		tab_buying_rates[i] = 1.0;
		tab_selling_rates[i] = 1.0;
	}
}

// Do informacji o aktualnym kursie:
double ExchangeTable::exchange_buying_rate (Currency curr) const{
	return tab_buying_rates[(int)curr];
}

double ExchangeTable::exchange_selling_rate (Currency curr) const{
	return tab_selling_rates[(int)curr];
}

ExchangeTable& ExchangeTable::exchangeRate(Currency curr) {
	is_fixed_exchange = true;
	currently_set_exchange = curr;
	return *this;
}

ExchangeTable& ExchangeTable::buyingRate(double v) {
	if(not is_fixed_exchange) return *this;
	tab_buying_rates[(int)currently_set_exchange] = v;
	return *this;
}

ExchangeTable& ExchangeTable::sellingRate(double v) {
	if(not is_fixed_exchange) return *this;
	tab_selling_rates[(int)currently_set_exchange] = v;
	return *this;
}

// Otwieranie konto:
CheckingAccount& Bank::openCheckingAccount(const Citizen& citizen) const {
	return gkb().create_checking_account(*this, citizen);	
}

SavingAccount& Bank::openSavingAccount(const Citizen& citizen) const {
	return gkb().create_saving_account(*this, citizen);	
}

CurrencyAccount& Bank::openCurrencyAccount(const Citizen& citizen, Currency curr) const {
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
	: bank(my_bank), currency(curr), citizen(citi), my_balance(0.0), my_id(new_id++) {}

Account::id_acc_t Account::id() const {
	return my_id;
}

double Account::transferCharge() const {
	return 0.0;
}

std::string Account::balance() const {
	std::string s =  std::to_string(my_balance) + name_currency(currency);
	return s;
}

void Account::deposit(double amount) {
	my_balance += amount;
}

void Account::withdraw(double amount) {
	if (amount > my_balance ) throw "za malo kasy";
	my_balance -= amount;
}

void Account::deposit(struct payment_format data) {
	if (data.curr != currency) throw "Zły typ waluty";
	deposit(data.amount);
}

void Account::withdraw(struct payment_format data) {
	if (data.curr != currency) throw "Zły typ waluty";
	withdraw(data.amount);
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


void Account::transfer(double amount, Account::id_acc_t recipient) {
	transfer(amount, recipient, "");
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

void CurrencyAccount::deposit(struct payment_format data) {
	if (data.curr == currency) return Account::deposit(data.amount);
	
	// Przewalutowanie
	double amount = data.amount;
	if (data.curr != Currency::ENC) {
		amount *= bank.exchange_selling_rate(data.curr);
	}
	amount /= bank.exchange_buying_rate(currency);

	Account::deposit(amount);
}

void CurrencyAccount::withdraw(struct payment_format data) {
	if (data.curr == currency) return Account::withdraw(data.amount);
	
	// Przewalutowanie
	double amount = data.amount * bank.exchange_selling_rate(currency);
	if (data.curr != Currency::ENC) {
		amount /= bank.exchange_buying_rate(data.curr);
	}

	Account::withdraw(amount);
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
	return (map_checking_account.count(id) != 0 ||
	        map_saving_account.count(id) != 0 ||
	        map_currency_account.count(id) != 0);
}

Account& Gkb::find_account(Account::id_acc_t id) {
	if (map_checking_account.count(id)) return *map_checking_account.at(id);
	if (map_saving_account.count(id))   return *map_saving_account.at(id);
	if (map_currency_account.count(id)) return *map_currency_account.at(id);
	throw "nie ma konta o tym id";					 // bardziej sensowny wyjątek stworzyć.
}

CheckingAccount& Gkb::create_checking_account(const Bank& bank, const Citizen& citizen) {
	CheckingAccount _checking_account(bank, citizen);
	auto shar = std::make_shared<CheckingAccount> (_checking_account);
	map_checking_account[_checking_account.id()] = shar;
	return *shar;
}

SavingAccount& Gkb::create_saving_account(const Bank& bank, const Citizen& citizen) {
	SavingAccount _saving_account(bank, citizen);
	auto shar = std::make_shared<SavingAccount> (_saving_account);
	map_saving_account[_saving_account.id()] = shar;
	return *shar;
}

CurrencyAccount& Gkb::create_currency_account(const Bank& bank, const Citizen& citizen, Currency curr){
	CurrencyAccount _currency_account(bank, citizen, curr);
	auto shar = std::make_shared<CurrencyAccount> (_currency_account);
	map_currency_account[_currency_account.id()] = shar;
	return *shar;
}
