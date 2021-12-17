#include <iostream>
#include <list>

/*
Type: Behavioural
Pattern: Observer

Lets you define a subscription mechanism to notify multiple objects about any events that happen to the object they’re observing.

Use the Observer pattern when changes to the state of one object may require changing other objects, 
	and the actual set of objects is unknown beforehand or changes dynamically.
Use the pattern when some objects in your app must observe others, but only for a limited time or in specific cases.
*/

// interface
class Observer {
	public:
		virtual ~Observer() {}
		virtual void update(const std::string& publisherMessage) = 0;
};

// interface
class Publisher {
	public:
		virtual ~Publisher() {}
		virtual void add(Observer* observer) = 0;
		virtual void remove(Observer* observer) = 0;
		virtual void notify() = 0;
};

class Publish : public Publisher {
	private:
		std::list<Observer*> observers;
		std::string message;
	public:
		void add(Observer* observer) override {
			observers.push_back(observer);
		}

		void remove(Observer* observer) override {
			observers.remove(observer);
		}

		void notify() override {
			for (Observer* observer: observers)
				observer->update(message);
		}

		void createMessage(std::string _message="Empty") {
			message = _message;
			notify();
		}
};

class Observe : public Observer {
	private:
		std::string publisherMessage;
		Publish& publish;
		const std::string self;

	public:
		Observe(const std::string _self, Publish& _publish) : self(_self), publish(_publish) {
			publish.add(this);
		}

		void update(const std::string& _publisherMessage) override {
			publisherMessage = _publisherMessage;
			std::cout << self << ": " << publisherMessage << '\n';
		}

		void unSubscribe() {
			publish.remove(this);
		}
};

void app() {
	Publish* publish = new Publish;

	Observe* observe1 = new Observe("Observe1", *publish);
	Observe* observe2 = new Observe("Observe2", *publish);
	
	publish->createMessage("Initial message.");
	publish->createMessage("Update message.");
	observe2->unSubscribe();
	publish->createMessage("Observe2 unsubscribed!");

	delete observe1;
	delete observe2;
	delete publish;
}

int main() {
	app();
}