#include <iostream>
#include <mutex>
#include <thread>

/*
Type: Creational
Pattern: Singleton

Class has only one instance, while providing a global access point to this instance.

*/

class Singleton {
	private:
	static Singleton* instance;
	static std::mutex mux;

	protected:
	std::string value;
	Singleton(const std::string val): value(val) {}

	public:
	// Singleton shouldn't be clonable
	Singleton(Singleton& other) = delete;
	// Singleton shouldn't be assignable
	void operator=(const Singleton&) = delete;
	static Singleton* GetInstance(const std::string& val);
	std::string Value() const {
		return value;
	}
};

// static methods should be defined cdoutside the class
Singleton* Singleton::instance{nullptr};
std::mutex Singleton::mux;

Singleton* Singleton::GetInstance(const std::string& val) {
	std::lock_guard<std::mutex> lock(mux);
	if (instance == nullptr)
		instance = new Singleton(val);
	return instance;
}

void ThreadFoo() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton* singleton = Singleton::GetInstance("Foo");
	std::cout << singleton->Value() << std::endl;
}

void ThreadBar() {
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	Singleton* singleton = Singleton::GetInstance("Bar");
	std::cout << singleton->Value() << std::endl;
}

int main() {
	std::thread t1(ThreadFoo);
	std::thread t2(ThreadBar);
	t1.join();
	t2.join();
}