#include "Product.h"
#include "Parts.cpp"
#include "Product.cpp"
#include <iostream>

/*
Type: Creational
Pattern: Builder

construct complex objects step by step.
Produce diff types and reps of obj using same construction code.

Use the Builder pattern to get rid of a “telescopic constructor”
Use the Builder pattern when you want your code to be able to create different representations of some product (for example, stone and wooden houses)
Use the Builder to construct Composite trees or other complex objects
*/

// interface
class Builder {
	public:
		virtual void setModel(CarT model) = 0;
		virtual void setSeats(int seats) = 0;
		virtual void setEngine(Engine* engine) = 0;
		virtual void setTransmission(Transmission transmission) = 0;
		virtual void setTripComputer(TripComputer* tripComputer) = 0;
		virtual void setGPSNavigator(GPSNavigator* gpsNav) = 0;
};

class CarBuilder : public Builder {
	private:
		CarT model;
		int seats;
		Engine* engine;
		Transmission transmission;
		TripComputer* tripComputer;
		GPSNavigator* gpsNav;

	public:
		void setModel(CarT model_) override {
			model = model_;
		}
		void setSeats(int seats_) override {
			seats = seats;
		}
		void setEngine(Engine* engine_) override {
			engine = engine_;
		}
		void setTransmission(Transmission transmission_) override {
			transmission = transmission_;
		}
		void setTripComputer(TripComputer* tripComputer_) override {
			tripComputer = tripComputer_;
		}
		void setGPSNavigator(GPSNavigator* gpsNav_) override {
			gpsNav = gpsNav_;
		}
		Car* getResult() {
			return new Car(model, seats, engine, transmission, tripComputer, gpsNav);
		}
};

class ManualBuilder : public Builder {
	private:
		CarT model;
		int seats;
		Engine* engine;
		Transmission transmission;
		TripComputer* tripComputer;
		GPSNavigator* gpsNav;

	public:
		void setModel(CarT model_) override {
			model = model_;
		}
		void setSeats(int seats_) override {
			seats = seats;
		}
		void setEngine(Engine* engine_) override {
			engine = engine_;
		}
		void setTransmission(Transmission transmission_) override {
			transmission = transmission_;
		}
		void setTripComputer(TripComputer* tripComputer_) override {
			tripComputer = tripComputer_;
		}
		void setGPSNavigator(GPSNavigator* gpsNav_) override {
			gpsNav = gpsNav_;
		}
		CarManual* getResult() {
			return new CarManual(model, seats, engine, transmission, tripComputer, gpsNav);
		}
};

class Director {
	public:
	void buildHondaCar(Builder* builder) {
		builder->setModel(CarT::Honda);
		builder->setSeats(2);
		builder->setEngine(new Engine(3.0, 0));
		builder->setTransmission(Transmission::SemiAutomatic);
		builder->setTripComputer(new TripComputer());
		builder->setGPSNavigator(new GPSNavigator());
	}
	void buildTataCar(Builder* builder) {
		builder->setModel(CarT::Tata);
		builder->setSeats(2);
		builder->setEngine(new Engine(2.0, 0));
		builder->setTransmission(Transmission::Manual);
		builder->setTripComputer(new TripComputer());
		builder->setGPSNavigator(new GPSNavigator());
	}
	void buildTeslaCar(Builder* builder) {
		builder->setModel(CarT::Tesla);
		builder->setSeats(4);
		builder->setEngine(new Engine(3.0, 0));
		builder->setTransmission(Transmission::Automatic);
		builder->setTripComputer(new TripComputer());
		builder->setGPSNavigator(new GPSNavigator());
	}
};

int main() {
	Director* director = new Director();

	CarBuilder* carBuilder = new CarBuilder();
	director->buildTeslaCar(carBuilder);

	Car* car = carBuilder->getResult();
	std::cout << car->getModel() << std::endl;

	ManualBuilder* manualBuilder = new ManualBuilder();
	director->buildHondaCar(manualBuilder);

	CarManual* manual = manualBuilder->getResult();
	std::cout << manual->print() << std::endl;
}