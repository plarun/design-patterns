package main

import "fmt"

type printer interface {
	printFile()
}

type epson struct{}

func (_epson *epson) printFile() {
	fmt.Println("Printing file in epson.")
}

type hp struct{}

func (_hp *hp) printFile() {
	fmt.Println("Printing file in hp.")
}

type computer interface {
	setPrinter(printer)
	print()
}

type mac struct {
	printer printer
}

func (_mac *mac) setPrinter(_printer printer) {
	_mac.printer = _printer
}

func (_mac *mac) print() {
	_mac.printer.printFile()
}

type win struct {
	printer printer
}

func (_win *win) setPrinter(_printer printer) {
	_win.printer = _printer
}

func (_win *win) print() {
	_win.printer.printFile()
}

func app(machine computer) {
	epsonPrinter := &epson{}
	hpPrinter := &hp{}

	machine.setPrinter(epsonPrinter)
	machine.print()
	machine.setPrinter(hpPrinter)
	machine.print()
}

func main() {
	app(&win{})
	app(&mac{})
}
