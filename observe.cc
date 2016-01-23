#include "observe.h"

void Observable::registrationObserver(Observer& observer) {
	observers.insert(std::make_pair(observers.size(), &observer));
}

void Observable::notifyAll() {
	for (auto it = observers.begin(); it != observers.end(); ++it)
		it->second->notify();	
}
