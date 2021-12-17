package main

import "fmt"

type train interface {
	arrive()
	depart()
	permitArrival()
}

type mediator interface {
	canArrive(train) bool
	notifyAboutDeparture()
}

type passengerTrain struct {
	mediator mediator
}

func (passTrain *passengerTrain) arrive() {
	if !passTrain.mediator.canArrive(passTrain) {
		fmt.Println("Passenger Train: Arrival blocked, waiting")
		return
	}
	fmt.Println("Passendger Train: Arrived")
}

func (passTrain *passengerTrain) depart() {
	fmt.Println("Passenger Train: Leaving")
	passTrain.mediator.notifyAboutDeparture()
}

func (passTrain *passengerTrain) permitArrival() {
	fmt.Println("Passenger Train: Arrival permitted, arriving")
	passTrain.arrive()
}

type expressTrain struct {
	mediator mediator
}

func (expTrain *expressTrain) arrive() {
	if !expTrain.mediator.canArrive(expTrain) {
		fmt.Println("Express Train: Arrival blocked, waiting")
		return
	}
	fmt.Println("Express Train: Arrived")
}

func (expTrain *expressTrain) depart() {
	fmt.Println("Express Train: Leaving")
	expTrain.mediator.notifyAboutDeparture()
}

func (expTrain *expressTrain) permitArrival() {
	fmt.Println("Express Train: Arrival permitted, arriving")
	expTrain.arrive()
}

type stationManager struct {
	isPlatformFree bool
	trainQueue     []train
}

func newStationManager() *stationManager {
	return &stationManager{
		isPlatformFree: true,
	}
}

func (manager *stationManager) canArrive(_train train) bool {
	if manager.isPlatformFree {
		manager.isPlatformFree = false
		return true
	}
	manager.trainQueue = append(manager.trainQueue, _train)
	return false
}

func (manager *stationManager) notifyAboutDeparture() {
	if !manager.isPlatformFree {
		manager.isPlatformFree = true
	}
	if len(manager.trainQueue) > 0 {
		firstTrainInQueue := manager.trainQueue[0]
		manager.trainQueue = manager.trainQueue[1:]
		firstTrainInQueue.permitArrival()
	}
}

func app() {
	stationManager := newStationManager()
	passengerTrain := &passengerTrain{
		mediator: stationManager,
	}
	expressTrain := &expressTrain{
		mediator: stationManager,
	}

	passengerTrain.arrive()
	expressTrain.arrive()
	passengerTrain.depart()
}

func main() {
	app()
}
