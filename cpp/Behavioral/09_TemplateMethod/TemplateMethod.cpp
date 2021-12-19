#include <iostream>

/*
Type: Behavioural
Pattern: Template Method

Defines the skeleton of an algorithm in the superclass but lets subclasses override specific steps of the algorithm without changing its structure.

Use the Template Method pattern when you want to let clients extend only particular steps of an algorithm, but not the whole algorithm or its structure.
Use the pattern when you have several classes that contain almost identical algorithms with some minor differences.
	As a result, you might need to modify all classes when the algorithm changes.
*/

// abstract class
class Network {
protected:
	std::string username;
	std::string password;

public:
	virtual bool login(std::string username, std::string password) const = 0;

	virtual bool sendData(std::string message) const = 0;

	virtual void logout() const = 0;

	bool post(std::string message) const {
		if (login(username, password)) {
			bool result = sendData(message);
			logout();
			return result;
		}
		return false;
	}
};

class Facebook : public Network {
public:
	Facebook(std::string _username, std::string _password) {
		username = _username;
		password = _password;
	}

	bool login(std::string _username, std::string _password) const override {
		std::cout << "Username: " << username << '\n';
		std::cout << "Password: ";
		for (int i=0; i<password.size(); ++i) std::cout << '*';
		std::cout << "\nSuccessfully logged in facebook.\n";
	}

	bool sendData(std::string data) const override {
		bool messagePosted = true;
		if (messagePosted) {
			std::cout << "Message posted: " << data << '\n';
			return true;
		}
		return false;
	}

	void logout() const override {
		std::cout << username << " logged out from facebook\n";
	}
};

class Twitter : public Network {
public:
	Twitter(std::string _username, std::string _password) {
		username = _username;
		password = _password;
	}

	bool login(std::string _username, std::string _password) const override {
		std::cout << "Username: " << username << '\n';
		std::cout << "Password: ";
		for (int i=0; i<password.size(); ++i) std::cout << '*';
		std::cout << "\nSuccessfully logged in twitter.\n";
	}

	bool sendData(std::string data) const override {
		bool messagePosted = true;
		if (messagePosted) {
			std::cout << "Message tweeted: " << data << '\n';
			return true;
		}
		return false;
	}

	void logout() const override {
		std::cout << username << " logged out from facebook\n";
	}
};

void app(int code) {
	std::string message = "Sample message";

	Network* network;
	if (code == 1) network = new Facebook("arunpandi", "12345");
	else if (code == 2) network = new Twitter("arunpandi", "12345");
	else return;

	network->post(message);
}

int main() {
	app(1);
	app(2);
}