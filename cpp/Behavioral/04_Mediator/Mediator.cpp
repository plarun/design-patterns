#include <iostream>
#include <string>

/*
Type: Behavioural
Pattern: Mediator

Lets you reduce chaotic dependencies between objects. 
The pattern restricts direct communications between the objects and forces them to collaborate only via a mediator object.

Use the Mediator pattern when it’s hard to change some of the classes because they are tightly coupled to a bunch of other classes.
Use the pattern when you can’t reuse a component in a different program because it’s too dependent on other components.
Use the Mediator when you find yourself creating tons of component subclasses just to reuse some basic behavior in various contexts.
*/

class BaseComponent;

// interface
class Mediator {
	public:
		virtual void notify(BaseComponent* sender, const std::string event) const = 0;
};

class BaseComponent {
	protected:
		Mediator* mediator;

	public:
		BaseComponent(Mediator* _mediator=nullptr) : mediator(_mediator) {}

		void setMediator(Mediator* _mediator) {
			mediator = _mediator;
		}
};

class Component1 : public BaseComponent {
	public:
		void taskA() {
			std::cout << "Component1: taskA\n";
			mediator->notify(this, "eventA");
		}

		void taskB() {
			std::cout << "Component1: taskB\n";
			mediator->notify(this, "eventB");
		}
};

class Component2 : public BaseComponent {
	public:
		void taskC() {
			std::cout << "Component2: taskC\n";
			mediator->notify(this, "eventC");
		}

		void taskD() {
			std::cout << "Component2: taskD\n";
			mediator->notify(this, "eventD");
		}
};

class ConcreteMediator : public Mediator {
	private:
		Component1* component1;
		Component2* component2;
	
	public:
		ConcreteMediator(Component1* _component1, Component2* _component2) : component1(_component1), component2(_component2) {
			component1->setMediator(this);
			component2->setMediator(this);
		}

		void notify(BaseComponent* sender, const std::string event) const override {
			if (event == "eventA") {
				component1->taskB();
				component2->taskC();
			} else if (event == "eventB") {
				component2->taskC();
			} else if (event == "eventC") {
				component2->taskD();
			}
		}
};

void app() {
	Component1* component1 = new Component1;
	Component2* component2 = new Component2;
	ConcreteMediator* mediator = new ConcreteMediator(component1, component2);

	component1->taskA();
	component1->taskB();
	component2->taskC();
	component2->taskD();

	delete component1;
	delete component2;
	delete mediator;
}

int main() {
	app();
}