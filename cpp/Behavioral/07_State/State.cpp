#include <iostream>
#include <typeinfo>

/*
Type: Behavioural
Pattern: State

Lets an object alter its behavior when its internal state changes. It appears as if the object changed its class.

Use the State pattern when you have an object that behaves differently depending on its current state, 
	the number of states is enormous, and the state-specific code changes frequently.
Use the pattern when you have a class polluted with massive conditionals that alter how the class behaves according to the current values of the class’s fields.
Use State when you have a lot of duplicate code across similar states and transitions of a condition-based state machine.
*/

class Context;

// abstract class
class State {
	protected:
		Context* context;
	
	public:
		virtual ~State() {}

		void setContext(Context* _context) {
			context = _context;
		}

		virtual void handle1() = 0;
		
		virtual void handle2() = 0;
};

class Context {
	private:
		State* state;

	public:
		Context(State* _state) : state(nullptr) {
			transitionTo(_state);
		}

		~Context() {
			delete state;
		}

		void transitionTo(State* _state) {
			std::cout << "Context: Transition to " << typeid(*_state).name() << "\n";
			if (!state) delete state;
			state = _state;
			state->setContext(this);
		}

		void request1() {
			state->handle1();
		}

		void request2() {
			state->handle2();
		}
};

class StateA : public State {
	public:
		void handle1() override;

		void handle2() override {
			std::cout << "StageA: handle2: no transition\n";
		}
};

class StateB : public State {
	public:
		void handle1() override {
			std::cout << "StateB: handle1: transition to StateA\n";
			context->transitionTo(new StateA);
		}

		void handle2() override {
			std::cout << "StageB: handle2: no transition\n";
		}
};

void StateA::handle1() {
	std::cout << "StateA: handle1: transition to StateB\n";
	context->transitionTo(new StateB);
}

void app() {
	Context* context = new Context(new StateA);
	context->request1();
	context->request2();
	
	delete context;
}

int main () {
	app();
}