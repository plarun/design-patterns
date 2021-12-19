#include <iostream>
#include <stack>

/*
Type: Behavioural
Pattern: Command

Turns a request into a stand-alone object that contains all information about the request. 
This transformation lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations.

Use the Command pattern when you want to parametrize objects with operations.
Use the Command pattern when you want to queue operations, schedule their execution, or execute them remotely.
Use the Command pattern when you want to implement reversible operations.

*/

// interface
class Command {
public:
	virtual ~Command() {}
	virtual void execute() const = 0;
};

class SimpleCommand : public Command {
private:
	std::string payLoad;

public:
	explicit SimpleCommand(std::string _payLoad) : payLoad(_payLoad) {}

	void execute() const override {
		std::cout << "Simple command: " << payLoad << "\n";
	}
};

class Receiver {
public:
	void doSomething(const std::string& str) {
		std::cout << "Receiver: " << str << "\n";
	}

	void doSomethingElse(const std::string& str) {
		std::cout << "Receiver: " << str << "\n";
	}
};

class ComplexCommand : public Command {
private:
	Receiver* receiver;
	std::string a;
	std::string b;

public:
	ComplexCommand(Receiver* _receiver, std::string _a, std::string _b) : receiver(_receiver), a(_a), b(_b) {}

	void execute() const override {
		std::cout << "Complex command: \n";
		receiver->doSomething(a);
		receiver->doSomethingElse(b);
	}
};

class Invoker {
private:
	Command* onStart;
	Command* onFinish;

public:
	~Invoker() {
		delete onStart;
		delete onFinish;
	}

	void setOnStart(Command* command) {
		onStart = command;
	}

	void setOnFinish(Command* command) {
		onFinish = command;
	}

	void doSomethingImportant() {
		std::cout << "Invoker: \n";
		if (onStart) onStart->execute();
		std::cout << "Invoker: doing something importan\n";
		if (onFinish) onFinish->execute();
	}
};

void app() {
	Invoker* invoker = new Invoker;
	invoker->setOnStart(new SimpleCommand("Simple work"));

	Receiver* receiver = new Receiver;
	invoker->setOnFinish(new ComplexCommand(receiver, "Send mail", "Save report"));
	invoker->doSomethingImportant();

	delete invoker;
	delete receiver;
}

int main() {
	app();
}