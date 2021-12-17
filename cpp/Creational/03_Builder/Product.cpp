#include "Product.h"
#include <iostream>


Car::Car(CarT model_, int seats_, Engine* engine_, Transmission transmission_, TripComputer* tripComputer_, GPSNavigator* gpsNav_) : 
	model(model_), seats(seats_), engine(engine_), transmission(transmission_), tripComputer(tripComputer_), gpsNav(gpsNav_) {}

CarT Car::getModel() const {
	return model;
}
int Car::getSeats() const {
	return seats;
}
Engine* Car::getEngine() const {
	return engine;
}
Transmission Car::getTranmission() const {
	return transmission;
}
TripComputer* Car::getTripComputer() const {
	return tripComputer;
}
GPSNavigator* Car::getGpsNavigator() const {
	return gpsNav;
}
int Car::getFuel() const {
	return fuel;
}
void Car::setFuel(double fuel_) {
	fuel = fuel_;
}


CarManual::CarManual(CarT model_, int seats_, Engine* engine_, Transmission transmission_, TripComputer* tripComputer_, GPSNavigator* gpsNav_) : 
	model(model_), seats(seats_), engine(engine_), transmission(transmission_), tripComputer(tripComputer_), gpsNav(gpsNav_) {}

std::string CarManual::print() const {
	std::string info;
	info += "Type of car: " + model + '\n';
	info += "Count of seats: " + seats + '\n';
	info += "Engine: volume - " + std::to_string(engine->getVolume()) + "; mileage - " + std::to_string(engine->getMileage()) + "\n";
	info += "Transmission: " + transmission + '\n';
	info += tripComputer ? "Trip Computer: Functional" + '\n' : "Trip Computer: N/A" + '\n';
	info += gpsNav ? "GPS Navigator: Functional" + '\n' : "GPS Navigator: N/A" + '\n';
	return info;
}
