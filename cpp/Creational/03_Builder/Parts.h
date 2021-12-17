#pragma once
#ifndef PARTS_H
#define PARTS_H

#include <string>
class Car;

enum CarT { 
	Honda = 0,
	Tata,
	Tesla
};

enum Transmission { 
	SingleSpeed = 0,
	Manual,
	Automatic,
	SemiAutomatic 
};

class Engine {
	private:
	const double volume;
	double mileage;
	bool started;

	public:
	Engine(double, double);
	void on();
	void off();
	bool isStarted() const;
	void go(double mileage_);
	double getVolume() const;
	double getMileage() const;
};

class GPSNavigator {
	private:
	std::string route;

	public:
	GPSNavigator();
	GPSNavigator(std::string manualRoute);
	std::string getRoute() const;
};

class TripComputer {
	private:
	Car* car;

	public:
	void setCar(Car* car_);
	void fuelLevel() const;
	void status() const;
};

#endif