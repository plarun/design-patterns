package main

import "fmt"

type shape interface {
	getType() string
	accept(visitor)
}

type square struct {
	side int
}

func (square *square) accept(visitor visitor) {
	visitor.visitForSquare(square)
}

func (square *square) getType() string {
	return "square"
}

type circle struct {
	radius int
}

func (circle *circle) accept(visitor visitor) {
	visitor.visitForCircle(circle)
}

func (circle *circle) getType() string {
	return "circle"
}

// visitor
type visitor interface {
	visitForCircle(*circle)
	visitForSquare(*square)
}

// concrete visitor
type areaCalculator struct{}

func (area *areaCalculator) visitForCircle(circle *circle) {
	fmt.Println("Calculating circle area")
}

func (area *areaCalculator) visitForSquare(square *square) {
	fmt.Println("Calculating square area")
}

// concrete visitor
type perimeterCalculator struct{}

func (perimeter *perimeterCalculator) visitForCircle(circle *circle) {
	fmt.Println("Calculating circle perimeter")
}

func (perimeter *perimeterCalculator) visitForSquare(square *square) {
	fmt.Println("Calculating square perimeter")
}

func app() {
	square := &square{side: 2}
	circle := &circle{radius: 3}

	areaCalculator := &areaCalculator{}
	square.accept(areaCalculator)
	circle.accept(areaCalculator)

	perimeterCalculator := &perimeterCalculator{}
	square.accept(perimeterCalculator)
	circle.accept(perimeterCalculator)
}

func main() {
	app()
}
