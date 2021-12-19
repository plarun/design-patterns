#include <iostream>
#include <vector>
#include <algorithm>

/*
Type: Behavioural
Pattern: Strategy

lets you define a family of algorithms, put each of them into a separate class, and make their objects interchangeable.

Use the Strategy pattern when you want to use different variants of an algorithm within an object and be able to switch from one algorithm to another during runtime.
Use the Strategy when you have a lot of similar classes that only differ in the way they execute some behavior.
Use the pattern to isolate the business logic of a class from the implementation details of algorithms that may not be as important in the context of that logic.
Use the pattern when your class has a massive conditional operator that switches between different variants of the same algorithm.
*/

// interface
class Strategy {
public:
	virtual ~Strategy() {}
	virtual std::string doAlgorithm(const std::vector<std::string>& data) const = 0;
};

class Context {
private:
	Strategy* strategy;

public:
	Context(Strategy* _strategy=nullptr) : strategy(_strategy) {}

	~Context() {
		delete strategy;
	}

	void setStrategy(Strategy* _strategy) {
		delete strategy;
		strategy = _strategy;
	}

	void task() const {
		std::cout << "Context: task: " << strategy->doAlgorithm(std::vector<std::string>{"a","b","c","d","e"}) << "\n";
	}
};

class StrategyA : public Strategy {
public:
	std::string doAlgorithm(const std::vector<std::string>& data) const override {
		std::string result;
		for (std::string word : data) result += word;
		std::sort(std::begin(result), std::end(result));
		return result;
	}
};

class StrategyB : public Strategy {
public:
	std::string doAlgorithm(const std::vector<std::string>& data) const override {
		std::string result;
		for (std::string word : data) result += word;
		std::sort(std::begin(result), std::end(result));
		std::reverse(std::begin(result), std::end(result));
		return result;
	}
};

void app() {
	Strategy* strategyA = new StrategyA;
	Context* context = new Context(strategyA);
	
	context->task();
	Strategy* strategyB = new StrategyA;
	context->setStrategy(strategyB);
	context->task();

	delete context;
	delete strategyA;
	delete strategyB;
}

int main() {
	app();
}