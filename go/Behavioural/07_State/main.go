package main

import (
	"fmt"
	"log"
)

type state interface {
	addItem(int) error
	requestItem() error
	insertMoney(int) error
	dispenseItem() error
}

// noItemState implements state
type noItemState struct {
	vendingMachine *vendingMachine
}

func (state *noItemState) addItem(count int) error {
	state.vendingMachine.itemCount += count
	state.vendingMachine.setState(state.vendingMachine.hasItem)
	return nil
}

func (state *noItemState) requestItem() error {
	return fmt.Errorf("item out of stock")
}

func (state *noItemState) insertMoney(money int) error {
	return fmt.Errorf("item out of stock")
}

func (state *noItemState) dispenseItem() error {
	return fmt.Errorf("item out of stock")
}

// hasItemState implements state
type hasItemState struct {
	vendingMachine *vendingMachine
}

func (state *hasItemState) addItem(count int) error {
	fmt.Printf("%d items added\n", count)
	state.vendingMachine.itemCount += count
	return nil
}

func (state *hasItemState) requestItem() error {
	if state.vendingMachine.itemCount == 0 {
		state.vendingMachine.setState(state.vendingMachine.noItem)
		return fmt.Errorf("no item present")
	}
	fmt.Printf("Item requestd\n")
	state.vendingMachine.setState(state.vendingMachine.itemRequested)
	return nil
}

func (state *hasItemState) insertMoney(money int) error {
	return fmt.Errorf("please select item first")
}

func (state *hasItemState) dispenseItem() error {
	return fmt.Errorf("please select item first")
}

// itemRequested implements state
type itemRequestedState struct {
	vendingMachine *vendingMachine
}

func (state *itemRequestedState) addItem(count int) error {
	return fmt.Errorf("item dispense in progress")
}

func (state *itemRequestedState) requestItem() error {
	return fmt.Errorf("item already requested")
}

func (state *itemRequestedState) insertMoney(money int) error {
	if money < state.vendingMachine.itemPrice {
		return fmt.Errorf("inserted money is less")
	}
	fmt.Println("Money entered is ok")
	state.vendingMachine.setState(state.vendingMachine.hasMoney)
	return nil
}

func (state *itemRequestedState) dispenseItem() error {
	return fmt.Errorf("please insert money first")
}

// hasMoneyState implements state
type hasMoneyState struct {
	vendingMachine *vendingMachine
}

func (state *hasMoneyState) addItem(count int) error {
	return fmt.Errorf("item dispense in progress")
}

func (state *hasMoneyState) requestItem() error {
	return fmt.Errorf("item dispense in progress")
}

func (state *hasMoneyState) insertMoney(money int) error {
	return fmt.Errorf("item out of stock")
}

func (state *hasMoneyState) dispenseItem() error {
	fmt.Println("Dispensing Item")
	state.vendingMachine.itemCount -= 1
	if state.vendingMachine.itemCount == 0 {
		state.vendingMachine.setState(state.vendingMachine.noItem)
	} else {
		state.vendingMachine.setState(state.vendingMachine.hasItem)
	}
	return nil
}

type vendingMachine struct {
	hasItem       state
	itemRequested state
	hasMoney      state
	noItem        state

	currentState state

	itemCount int
	itemPrice int
}

func (machine *vendingMachine) setState(newState state) {
	machine.currentState = newState
}

func newVendingMachine(itemCount, itemPrice int) *vendingMachine {
	vendorMachine := &vendingMachine{
		itemCount: itemCount,
		itemPrice: itemPrice,
	}

	vendorMachine.hasItem = &hasItemState{vendorMachine}
	vendorMachine.itemRequested = &itemRequestedState{vendorMachine}
	vendorMachine.hasMoney = &hasMoneyState{vendorMachine}
	vendorMachine.noItem = &noItemState{vendorMachine}
	vendorMachine.setState(vendorMachine.hasItem)
	return vendorMachine
}

func (vendorMachine *vendingMachine) addItem(count int) error {
	return vendorMachine.currentState.addItem(count)
}

func (vendorMachine *vendingMachine) requestItem() error {
	return vendorMachine.currentState.requestItem()
}

func (vendorMachine *vendingMachine) insertMoney(money int) error {
	return vendorMachine.currentState.insertMoney(money)
}

func (vendorMachine *vendingMachine) dispenseItem() error {
	return vendorMachine.currentState.dispenseItem()
}

func app() {
	vendingMachine := newVendingMachine(1, 10)

	err := vendingMachine.requestItem()
	if err != nil {
		log.Fatal(err.Error())
	}

	err = vendingMachine.insertMoney(10)
	if err != nil {
		log.Fatal(err.Error())
	}

	err = vendingMachine.dispenseItem()
	if err != nil {
		log.Fatal(err.Error())
	}

	err = vendingMachine.addItem(2)
	if err != nil {
		log.Fatal(err.Error())
	}

	err = vendingMachine.requestItem()
	if err != nil {
		log.Fatal(err.Error())
	}

	err = vendingMachine.insertMoney(10)
	if err != nil {
		log.Fatal(err.Error())
	}

	err = vendingMachine.dispenseItem()
	if err != nil {
		log.Fatal(err.Error())
	}
}

func main() {
	app()
}
