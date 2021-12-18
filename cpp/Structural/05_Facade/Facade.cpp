#include <iostream>

/*
Type: Structural
Pattern: Facade

Provides a simplified interface to a library, a framework, or any other complex set of classes.

Use the Facade pattern when you need to have a limited but straightforward interface to a complex subsystem.
Use the Facade when you want to structure a subsystem into layers.
*/

class SubSystem1 {
public:
	std::string operation1() const {
		return "Subsystem1: Ready\n";
	}
	std::string operationN() const {
		return "Subsystem1: Go\n";
	}
};

class SubSystem2 {
public:
	std::string operation1() const {
		return "Subsystem2: Ready\n";
	}
	std::string operationN() const {
		return "Subsystem2: Go\n";
	}
};

class Facade {
protected:
	SubSystem1* subsys1;
	SubSystem2* subsys2;

public:
	Facade(SubSystem1* s1=nullptr, SubSystem2* s2=nullptr) {
		subsys1 = s1 ? s1 : new SubSystem1;
		subsys2 = s2 ? s2 : new SubSystem2; 
	}
	~Facade() {
		delete subsys1;
		delete subsys2;
	}
	std::string operation() const {
		std::string result = "Facade init\n";
		result += subsys1->operation1();
		result += subsys2->operation1();
		result += "Facade Go\n";
		result += subsys1->operationN();
		result += subsys2->operationN();
		return result;
	}
};

void app(Facade* facade) {
	std::cout << facade->operation();
	return;
}

int main() {
	SubSystem1* s1 = new SubSystem1;
	SubSystem2* s2 = new SubSystem2;
	Facade* facade = new Facade(s1, s2);
	app(facade);
	
	delete s1;
	delete s2;
	delete facade;
}
