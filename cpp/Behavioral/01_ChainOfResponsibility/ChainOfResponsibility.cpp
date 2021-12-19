#include <iostream>
#include <ctime>
#include <thread>
#include <unordered_map>

/*
Type: Behavioural
Pattern: Chain of responsibility

Lets you pass requests along a chain of handlers. Upon receiving a request, 
	each handler decides either to process the request or to pass it to the next handler in the chain.


*/

// abstract class
class Middleware {
private:
	Middleware* next;

public:
	Middleware* linkWith(Middleware* nextMiddleware) {
		next = nextMiddleware;
		return next;
	}

	virtual bool check(std::string email, std::string password) = 0;

protected:
	bool checkNext(std::string email, std::string password) {
		if (next == nullptr) return true;
		return next->check(email, password);
	}
};

class Server {
private:
	std::unordered_map<std::string, std::string> users;
	Middleware* middleware;

public:
	void setMiddleware(Middleware* _middleware) {
		middleware = _middleware;
	}

	bool login(std::string email, std::string password) {
		if (middleware->check(email, password)) return true;
		return false;
	}

	void addUser(std::string email, std::string password) {
		users.insert(std::make_pair(email, password));
	}

	bool hasEmail(std::string email) {
		return users.find(email) != users.end();
	}

	bool isValidPassword(std::string email, std::string password) {
		return users.at(email) == password;
	}
};

class ThrottlingMiddleware : public Middleware {
private:
	int requestPerMinute;
	int request;
	time_t currentTime;

	time_t getCurrentTimeInMilliseconds() {
		return time(nullptr) * 1000;
	}

public:
	ThrottlingMiddleware(int reqPerMinute) {
		requestPerMinute = reqPerMinute;
		currentTime = getCurrentTimeInMilliseconds();
	}

	bool check(std::string email, std::string password) {
		time_t now = getCurrentTimeInMilliseconds();
		if (now > currentTime + 60000) {
			request = 0;
			currentTime = getCurrentTimeInMilliseconds();
		}
		++request;
		if (request > requestPerMinute) {
			std::terminate();
		}
		return checkNext(email, password);
	}
};

class UserExistsMiddleware : public Middleware {
private:
	Server* server;

public:
	UserExistsMiddleware(Server* _server): server(_server) {}

	bool check(std::string email, std::string password) {
		if (!server->hasEmail(email)) return false;
		if (!server->isValidPassword(email, password)) return false;
		return checkNext(email, password);
	}
};

class RoleCheckMiddleware : public Middleware {
private:
	const std::string adminId = "admin@domain.com";

public:
	bool check(std::string email, std::string password) {
		if (email == adminId) return true;
		return checkNext(email, password);
	}
};

void app(Server* server) {
	Middleware* middleware = new ThrottlingMiddleware(2);
	middleware
		->linkWith(new UserExistsMiddleware(server))
		->linkWith(new RoleCheckMiddleware());
	server->setMiddleware(middleware);

	bool isSuccess = false;
	std::string email, password;

	while (!isSuccess) {
		std::cout << "email: ";
		std::cin >> email;
		std::cout << "password: ";
		std::cin >> password;
		isSuccess = server->login(email, password);
	}
}

int main() {
	Server* server = new Server();
	server->addUser("admin@domain.com", "1234");
	server->addUser("arun@domain.com", "5678");
	app(server);
}