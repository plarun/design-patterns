#include "Product.h"
#include <iostream>

Engine::Engine(double volume_, double mileage_) : volume(volume_), mileage(mileage_) {}

void Engine::on() {
	started = true;
}
void Engine::off() {
	started = false;
}
bool Engine::isStarted() const {
	return started;
}
void Engine::go(double mileage_) {
	if (started) mileage = mileage_;
	else std::cout << "Engine is not started\n";
}
double Engine::getVolume() const {
	return volume;
}
double Engine::getMileage() const {
	return mileage;
}


GPSNavigator::GPSNavigator() {
	route = "221b, Baker Street, Chennai to Kerala, 8-10 Broadway, India";
}
GPSNavigator::GPSNavigator(std::string manualRoute) {
	route = manualRoute;
}
std::string GPSNavigator::getRoute() const {
	return route;
}


void TripComputer::setCar(Car* car_) {
	car = car_;
}
void TripComputer::fuelLevel() const {
	std::cout << "Fuel level: " << car->getFuel() << std::endl;
}
void TripComputer::status() const {
	if (car->getEngine()->isStarted())
		std::cout << "Car is started\n";
	else
		std::cout << "Car is not started\n";
}