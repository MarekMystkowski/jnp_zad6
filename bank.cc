#include "bank.h"


// BankBuilder:															DOPISAĆ WYJĄTKI!!
BankBuilder::BankBuilder() {}

BankBuilder& BankBuilder::name(const std::string name) {
    this->name = name;
    return *this;
}

BankBuilder& BankBuilder::checkingAccount() {
    parameters[account_type::CHECKING][account_parameters::IS]._bool = true;
    currently_set_type = account_type::CHECKING;
    return *this;
}

BankBuilder& BankBuilder::savinggAccount() {
    parameters[account_type::SAVING][account_parameters::IS]._bool = true;
    currently_set_type = account_type::SAVING;
    return *this;
}

BankBuilder& BankBuilder::currencyAccount() {
    parameters[account_type::CURRENCY][account_parameters::IS]._bool = true;
    currently_set_type = account_type::CURRENCY;
    return *this;
}

BankBuilder& BankBuilder::monthlyCharge(double value) {
	parameters[currently_set_type][MONTHLY_CHARGE]._double = value;
	return *this;
}

BankBuilder& BankBuilder::transferCharge(double value) {
	parameters[currently_set_type][TRANSFER_CHARGE]._double = value;
	return *this;
}

BankBuilder& BankBuilder::interestRate(double value) {
	parameters[currently_set_type][INTEREST_RATE]._double = value;
	return *this;
}

Bank& BankBuilder::createBank() {
	return Bank(name, parameters);
}


// Gkb:
BankBuilder& Gkb::bankApplication() const {
	return BankBuilder();	
}

Gkb& Gkb::gkb() {
	static Gkb _gkb;
	return _gkb;
}


