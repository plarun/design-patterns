#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include "Parts.h"

class Car {
	private:
		CarT model;
		int seats;
		Engine* engine;
		Transmission transmission;
		TripComputer* tripComputer;
		GPSNavigator* gpsNav;
		double fuel = 0;

	public:
		Car(CarT, int, Engine*, Transmission, TripComputer*, GPSNavigator*);
		CarT getModel() const;
		int getSeats() const;
		Engine* getEngine() const;
		Transmission getTranmission() const;
		TripComputer* getTripComputer() const;
		GPSNavigator* getGpsNavigator() const;
		int getFuel() const;
		void setFuel(double fuel_);
};

class CarManual {
	private:
		CarT model;
		int seats;
		Engine* engine;
		Transmission transmission;
		TripComputer* tripComputer;
		GPSNavigator* gpsNav;

	public:
		CarManual(CarT, int, Engine*, Transmission, TripComputer*, GPSNavigator*);
		std::string print() const;
};

#endif