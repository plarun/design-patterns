#include <iostream>
#include <algorithm>

/*
Type: Structural
Pattern: Adapter

Allows objects with incompatible interfaces to collaborate

Use the Adapter class when you want to use some existing class, but its interface isn’t compatible with the rest of your code.
Use the pattern when you want to reuse several existing subclasses that lack some common functionality that can’t be added to the superclass.
*/

class Target {
public:
	virtual ~Target() = default;
	virtual std::string request() const {
		return "Target: The default target's behavior";
	}
};

class Adaptee {
public:
	std::string specificRequest() const {
		return "eetpadA eht fo roivaheb laicepS";
	}
};

class Adapter : public Target {
private:
	Adaptee* adaptee;

public:
	Adapter(Adaptee* adaptee_) : adaptee(adaptee_) {}
	std::string request() const override {
		std::string toRev = adaptee->specificRequest();
		std::reverse(toRev.begin(), toRev.end());
		return "Adapter: (translated) " + toRev;
	}
};

void app() {
	Target* target = new Target();
	std::cout << target->request() << std::endl;

	Adaptee* adaptee = new Adaptee();
	std::cout << adaptee->specificRequest() << std::endl;

	Adapter* adapter = new Adapter(adaptee);
	std::cout << adapter->request() << std::endl;

	delete target;
	delete adaptee;
	delete adapter;
}

int main() {
	app();
}