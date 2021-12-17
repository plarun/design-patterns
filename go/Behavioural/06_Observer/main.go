package main

import "fmt"

type observer interface {
	update(string)
	getID() string
}

type customer struct {
	id string
}

func (cust *customer) update(itemName string) {
	fmt.Printf("sending email to customer %s for item %s\n", cust.id, itemName)
}

func (cust *customer) getID() string {
	return cust.id
}

type subject interface {
	register(observer)
	deRegister(observer)
	notifyAll()
}

type item struct {
	observers []observer
	name      string
	inStock   bool
}

func newItem(name string) *item {
	return &item{name: name}
}

func (_item *item) updateAvailability() {
	fmt.Printf("Item %s is now in stock\n", _item.name)
	_item.inStock = true
	_item.notifyAll()
}

func (_item *item) register(_observer observer) {
	_item.observers = append(_item.observers, _observer)
}

func (_item *item) deRegister(_observer observer) {
	_item.observers = removeFromSlice(_item.observers, _observer)
}

func (_item *item) notifyAll() {
	for _, observer := range _item.observers {
		observer.update(_item.name)
	}
}

func removeFromSlice(observers []observer, observerToDel observer) []observer {
	size := len(observers)
	for i, observer := range observers {
		if observer.getID() == observerToDel.getID() {
			observers[size-1], observers[i] = observers[i], observers[size-1]
			return observers[:size-1]
		}
	}
	return observers
}

func app() {
	shirt := newItem("Nike shirt")

	cust1 := &customer{id: "arun@gmail.com"}
	cust2 := &customer{id: "pandi@gmail.com"}

	shirt.register(cust1)
	shirt.register(cust2)
	shirt.updateAvailability()
}

func main() {
	app()
}
