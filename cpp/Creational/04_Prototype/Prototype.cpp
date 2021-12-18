#include <iostream>
#include <string>

/*
Type: Creational
Pattern: Prototype

Use the Prototype pattern when your code shouldn’t depend on the concrete classes of objects that you need to copy.
Use the pattern when you want to reduce the number of subclasses that only differ in the way they initialize their respective objects.
	Somebody could have created these subclasses to be able to create objects with a specific configuration.


*/

// interface
class Shape {

public:
	virtual ~Shape() {};
	virtual Shape* clone() = 0;
	virtual std::string type() = 0;
};

class Circle : public Shape {

public:
	~Circle() {}
	Shape* clone() {
		return new Circle();
	}
	std::string type() {
		return "Circle";
	}
};

class Square : public Shape {

public:
	~Square() {}
	Shape* clone() {
		return new Square();
	}
	std::string type() {
		return "Square";
	}
};

class Client {

private:
	static Shape* types[2];
	static int n_types;

public:
	static void init() {
		types[0] = new Circle();
		types[1] = new Square();
	}
	static void remove() {
		delete types[0];
		delete types[1];
	}
	static Shape* make(const int index) {
		if (index >= n_types) return nullptr;
		return types[index]->clone();
	}
};

Shape* Client::types[2];
int Client::n_types = 2;

void app() {
	Client::init();

	Shape* circle = Client::make(0);
	std::cout << circle->type() << std::endl;
	Shape* clonedCircle = circle->clone();
	std::cout << clonedCircle->type() << std::endl;

	delete circle;
	delete clonedCircle;

	Shape* square = Client::make(1);
	std::cout << square->type() << std::endl;
	Shape* clonedSquare = square->clone();
	std::cout << clonedSquare->type() << std::endl;

	delete square;
	delete clonedSquare;

	Client::remove();
}

int main() {
	app();
}