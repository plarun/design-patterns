package main

import "fmt"

// interface
type computer interface {
	connectionPort()
}

// mac implements computer
type mac struct{}

func (_mac *mac) connectionPort() {
	fmt.Println("Connected to mac.")
}

// windows implements computer
type windows struct{}

func (_windows *windows) connectionPort() {
	fmt.Println("Connected to windows.")
}

// windowsAdapter implements computer
type windowsAdapter struct {
	windowMachine *windows
}

func (win *windowsAdapter) connectionPort() {
	fmt.Println("Adapter converts lightning signal to USB")
	win.windowMachine.connectionPort()
}

type client struct{}

func (_client *client) connect(machine computer) {
	machine.connectionPort()
}

func app() {
	machine := &client{}

	mac := &mac{}
	machine.connect(mac)

	win := &windows{}
	winAdapter := &windowsAdapter{
		windowMachine: win,
	}
	machine.connect(winAdapter)
}

func main() {
	app()
}
