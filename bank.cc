#include "bank.h"
#include <memory>

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
}


// BankBuilder:															DOPISAĆ WYJĄTKI!!
BankBuilder::BankBuilder() {
	default_account_parameters (parameters);
}

BankBuilder& BankBuilder::name(const std::string _name) {
    bank_name = _name;
    return *this;
}

BankBuilder& BankBuilder::checkingAccount() {
    currently_set_type = account_type::CHECKING;
    return *this;
}

BankBuilder& BankBuilder::savingAccount() {
    currently_set_type = account_type::SAVING;
    return *this;
}

BankBuilder& BankBuilder::currencyAccount() {
    currently_set_type = account_type::CURRENCY;
    return *this;
}

BankBuilder& BankBuilder::monthlyCharge(double value) {
	parameters[(int)currently_set_type][(int)account_parameters::MONTHLY_CHARGE] = value;
	return *this;
}

BankBuilder& BankBuilder::transferCharge(double value) {
	parameters[(int)currently_set_type][(int)account_parameters::TRANSFER_CHARGE] = value;
	return *this;
}

BankBuilder& BankBuilder::interestRate(double value) {
	parameters[(int)currently_set_type][(int)account_parameters::INTEREST_RATE] = value;
	return *this;
}

Bank& BankBuilder::createBank() const {
	Bank bank = Bank(bank_name, parameters);
	return *std::make_shared<Bank> (bank);
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


