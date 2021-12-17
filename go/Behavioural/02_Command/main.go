package main

import "fmt"

type command interface {
	execute()
}

type button struct {
	command command
}

func (btn *button) press() {
	btn.command.execute()
}

type device interface {
	on()
	off()
}

type onCommand struct {
	device device
}

func (onCmd *onCommand) execute() {
	onCmd.device.on()
}

type offCommand struct {
	device device
}

func (offCmd *offCommand) execute() {
	offCmd.device.off()
}

type radio struct {
	isRunning bool
}

func (_radio *radio) on() {
	_radio.isRunning = true
	fmt.Println("Radio on")
}

func (_radio *radio) off() {
	_radio.isRunning = false
	fmt.Println("Radio off")
}

type tv struct {
	isRunning bool
}

func (_tv *tv) on() {
	_tv.isRunning = true
	fmt.Println("Tv on")
}

func (_tv *tv) off() {
	_tv.isRunning = false
	fmt.Println("Tv off")
}

func app(device device) {
	onCommand := &onCommand{device}
	offCommand := &offCommand{device}
	onButton := &button{
		command: onCommand,
	}
	offButton := &button{
		command: offCommand,
	}

	onButton.press()
	offButton.press()
}

func main() {
	radio := &radio{}
	tv := &tv{}
	app(radio)
	app(tv)
}
