package main

import "fmt"

type memento struct {
	state string
}

func (_memento *memento) getSavedState() string {
	return _memento.state
}

type originator struct {
	state string
}

func (_originator *originator) createMemento() *memento {
	return &memento{state: _originator.state}
}

func (_originator *originator) restoreMemento(_memento *memento) {
	_originator.state = _memento.getSavedState()
}

func (_originator *originator) setState(state string) {
	_originator.state = state
}

func (_originator *originator) getState() string {
	return _originator.state
}

type careTaker struct {
	history []*memento
}

func (_careTaker *careTaker) addMemento(_memento *memento) {
	_careTaker.history = append(_careTaker.history, _memento)
}

func (_careTaker *careTaker) getMemento(index int) *memento {
	if index < 0 || index >= len(_careTaker.history) {
		return nil
	}
	return _careTaker.history[index]
}

func addStateUtil(state string, careTaker *careTaker, originator *originator) {
	originator.setState(state)
	fmt.Println("State: ", originator.getState())
	careTaker.addMemento(originator.createMemento())
}

func restoreStateUtil(index int, careTaker *careTaker, originator *originator) {
	originator.restoreMemento(careTaker.getMemento(index))
	fmt.Println("State: ", originator.getState())
}

func app() {
	careTaker := &careTaker{
		history: make([]*memento, 0),
	}
	originator := &originator{}

	addStateUtil("A", careTaker, originator)
	addStateUtil("B", careTaker, originator)
	addStateUtil("C", careTaker, originator)

	restoreStateUtil(1, careTaker, originator)
	restoreStateUtil(0, careTaker, originator)
}

func main() {
	app()
}
