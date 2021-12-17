#include <iostream>
#include <unordered_map>

/*
Type: Structural
Pattern: Fly Weight

Use the Flyweight pattern only when your program must support a huge number of objects which barely fit into available RAM

*/

class SharedState {
	public:
		std::string brand;
		std::string color;
		std::string model;
		
		SharedState(const std::string& _brand, const std::string& _color, const std::string& _model):
			brand(_brand), color(_color), model(_model) {}
		
		friend std::ostream &operator<<(std::ostream& os, const SharedState& ss) {
			return os 	<< "{" 
						<< ss.brand << "," 
						<< ss.model << "," 
						<< ss.color 
						<< "}";
		}
};

class UniqueState {
	public:
		std::string owner;
		std::string plates;

		UniqueState(std::string _owner, std::string _plates) : owner(_owner), plates(_plates) {}

		friend std::ostream &operator<<(std::ostream& os, const UniqueState& us) {
			return os 	<< "{" 
						<< us.owner << "," 
						<< us.plates 
						<< "}";
		}
};

/* 
shared state(intrinsic state) cant be changed
unique state(extrinsic state) are passed in via params
*/
class FlyWeight {
	private:
		SharedState* sharedState;

	public:
		FlyWeight(const SharedState* _sharedState): sharedState(new SharedState(*_sharedState)) {}

		FlyWeight(const FlyWeight& other): sharedState(new SharedState(*other.sharedState)) {}

		~FlyWeight() {
			delete sharedState;
		}

		SharedState* getSharedState() const {
			return sharedState;
		}

		void operation(const UniqueState& uniqueState) const {
			std::cout 	<< "Flyweight: Displaying shared (" 
						<< *sharedState 
						<< ") and unique (" 
						<< uniqueState << ") state.\n";
		}
};

class FlyWeightFactory {
	private:
		std::unordered_map<std::string, FlyWeight> flyWeights;

		std::string getKey(const SharedState& ss) const {
			return ss.brand + "_" + ss.model + "_" + ss.color;
		}

		void insert(const SharedState& sharedState) {
			flyWeights.insert(std::make_pair(getKey(sharedState), FlyWeight(&sharedState)));
		}

	public:
		FlyWeightFactory(std::initializer_list<SharedState> sharedStates) {
			for (const SharedState& sharedState: sharedStates)
				insert(sharedState);
		}

		FlyWeight getFlyWeight(const SharedState& sharedState) {
			std::string key = getKey(sharedState);
			if (flyWeights.find(key) == flyWeights.end())
				insert(sharedState);
			return flyWeights.at(key);
		}

		void listFlyWeights() const {
			for (const std::pair<std::string, FlyWeight>& flyWeight: flyWeights)
				std::cout << flyWeight.first << std::endl;
		}
};

void app(FlyWeightFactory& flyWeightFactory, const std::string& plates, const std::string& owner, const std::string& brand, const std::string& model, const std::string& color) {
	const FlyWeight& flyWeight = flyWeightFactory.getFlyWeight({brand, model, color});
	flyWeight.operation({owner, plates});
}

int main() {
	FlyWeightFactory* factory = new FlyWeightFactory({
		{"Chevrolet", "Camaro2018", "pink"}, 
		{"Mercedes Benz", "C300", "black"}, 
		{"Mercedes Benz", "C500", "red"}, 
		{"BMW", "M5", "red"}, 
		{"BMW", "X6", "white"}
	});

	factory->listFlyWeights();
	app(*factory, "CL234IR", "James Doe", "BMW", "M5", "red");
    app(*factory, "CL234IR", "James Doe", "BMW", "X1", "red");
	factory->listFlyWeights();

	delete factory;
}