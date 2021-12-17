#include <iostream>
#include <ctime>
#include <vector>

/*
Type: Behavioural
Pattern: Memento

Lets you save and restore the previous state of an object without revealing the details of its implementation.

Use the Memento pattern when you want to produce snapshots of the object’s state to be able to restore a previous state of the object.
Use the pattern when direct access to the object’s fields/getters/setters violates its encapsulation.
*/

// interface
class Memento {
	public:
		virtual std::string getName() const = 0;
		virtual std::string getDate() const = 0;
		virtual std::string getState() const = 0;
};

class ConcreteMemento : public Memento {
	private:
		std::string state;
		std::string date;

	public:
		ConcreteMemento(std::string _state) : state(_state) {
			std::time_t now = std::time(0);
			date = std::ctime(&now);
		}

		std::string getState() const override {
			return state;
		}

		std::string getName() const override {
			return date + " / (" + state + "...)";
		}

		std::string getDate() const override {
			return date;
		}
};

class Originator {
	private:
		std::string state;
		
		std::string generateRandomString(int length = 10) {
			const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
			int strLength = sizeof(alphanum)-1;
			std::string randomString;
			for (int i=0; i<5; ++i)
				randomString += alphanum[std::rand() % strLength];
			return randomString;
		}

	public:
		Originator(std::string _state) : state(_state) {}

		void task() {
			state = generateRandomString(30);
		}

		Memento* save() {
			return new ConcreteMemento(state);
		}

		void restore(Memento* memento) {
			state = memento->getState();
		}
};

class Caretaker {
	private:
		std::vector<Memento*> history;
		Originator* originator;

	public:
		Caretaker(Originator* _originator) : originator(_originator) {}

		void backup() {
			history.push_back(originator->save());
		}

		void undo() {
			if (history.size() == 0) return;
			Memento* lastMemento = history.back();
			history.pop_back();
			try {
				originator->restore(lastMemento);
			} catch (...) {
				this->undo();
			}
		}

		void showHistory() const {
			for (Memento* memento: history) std::cout << memento->getName() << "\n";
		}
};

void app() {
	Originator* originator = new Originator("Task1");
	Caretaker* caretaker = new Caretaker(originator);

	caretaker->backup();
	originator->task();
	caretaker->backup();
	originator->task();
	caretaker->backup();
	originator->task();

	std::cout << "\n";
	caretaker->showHistory();
	caretaker->undo();
	caretaker->showHistory();
	caretaker->undo();
	caretaker->showHistory();

	delete caretaker;
	delete originator;
}

int main() {
	app();
}