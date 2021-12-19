#include <iostream>
#include <array>

/*
Type: Behavioural
Pattern: Visitor

Lets you separate algorithms from the objects on which they operate.

Use the Visitor when you need to perform an operation on all elements of a complex object structure (for example, an object tree).
Use the Visitor to clean up the business logic of auxiliary behaviors.
Use the pattern when a behavior makes sense only in some classes of a class hierarchy, but not in others.
*/

class ComponentA;
class ComponentB;

// interface
class Visitor {
public:
	virtual void visitComponentA(const ComponentA* element) const = 0;
	virtual void visitComponentB(const ComponentB* element) const = 0;
};

// interface
class Component {
public:
	virtual ~Component() {}
	virtual void accept(Visitor* visitor) const = 0;
};

class ComponentA : public Component {
public:
	void accept(Visitor* visitor) const override {
		visitor->visitComponentA(this);
	}

	std::string task() const {
		return "task A";
	}
};

class ComponentB : public Component {
public:
	void accept(Visitor* visitor) const override {
		visitor->visitComponentB(this);
	}

	std::string task() const {
		return "task B";
	}
};

class Visitor1 : public Visitor {
public:
	void visitComponentA(const ComponentA* element) const override {
		std::cout << "Visitor1: " << element->task() << '\n';
	}

	void visitComponentB(const ComponentB* element) const override {
		std::cout << "Visitor1: " << element->task() << '\n';
	}
};

class Visitor2 : public Visitor {
public:
	void visitComponentA(const ComponentA* element) const override {
		std::cout << "Visitor2: " << element->task() << '\n';
	}

	void visitComponentB(const ComponentB* element) const override {
		std::cout << "Visitor2: " << element->task() << '\n';
	}
};

void app(std::array<const Component*, 2> components, Visitor* visitor) {
	for (const Component* component: components)
		component->accept(visitor);
}

int main() {
	std::array<const Component*, 2> components = {new ComponentA, new ComponentB};

	Visitor1* visitor1 = new Visitor1;
	app(components, visitor1);

	Visitor2* visitor2 = new Visitor2;
	app(components, visitor2);

	for (const Component* component : components) delete component;
	delete visitor1;
	delete visitor2;
}