#include "interstellarclock.h"
#include <iostream>
using namespace std;

unsigned long long InterstellarClock::hours() const {
    return _hours;
}

Time InterstellarClock::time() const {
    return _hours % HOURS_IN_DAY;
}

Date InterstellarClock::date() const {
    return _hours / HOURS_IN_DAY;
}

InterstellarClock& InterstellarClock::nextHour() {
	// Naliczane są opłaty 30 *k dnia o godzinie 23:59 (pod koniec dnia) , gdzie k >= 1 , naturalne.
	 if (_hours % (HOURS_IN_DAY * DAYS_IN_MONTH) == 0 && _hours != 0)
		notify();
    _hours++;
    return *this;
}

InterstellarClock& InterstellarClock::nextDay() {
    for (Time i = 0; i < HOURS_IN_DAY; i++)
        nextHour();
    return *this;
}

InterstellarClock& InterstellarClock::nextMonth() {
    for (Date i = 0; i < DAYS_IN_MONTH; i++)
        nextDay();
    return *this;
}

InterstellarClock& interstellarClock() {
    static InterstellarClock interstellarClock;
    return interstellarClock;
}


void InterstellarClock::registration_account(Account* acc) {
	 observers.insert(std::make_pair(observers.size(), acc));
}

void InterstellarClock::notify() const {
    for (auto it = observers.begin(); it != observers.end(); ++it)
        it->second->notify();
}
