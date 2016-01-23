#ifndef __gsb__observe__
#define __gsb__observe__
#include <map>

class Observer {
	public:
		virtual void notify() = 0;

};

class Observable {
	public:
		void registrationObserver(Observer& observer);
		
	protected:
		void notifyAll();
		
	private:
		std::map<int, Observer*> observers;
};

#endif /* defined(__gsb__observe__) */
