package main

import "fmt"

// interface for shoe product
type iShoe interface {
	setLogo(logo string)
	getLogo() string
	setSize(size int)
	getSize() int
}

type shoe struct {
	logo string
	size int
}

func (_shoe *shoe) setLogo(logo string) {
	_shoe.logo = logo
}

func (_shoe *shoe) getLogo() string {
	return _shoe.logo
}

func (_shoe *shoe) setSize(size int) {
	_shoe.size = size
}

func (_shoe *shoe) getSize() int {
	return _shoe.size
}

// adidasShoe implements iShoe
type adidasShoe struct {
	shoe
}

// nikeShoe implements iShoe
type nikeShoe struct {
	shoe
}

// interface for shirt product
type iShirt interface {
	setLogo(logo string)
	getLogo() string
	setSize(size int)
	getSize() int
}

type shirt struct {
	logo string
	size int
}

func (_shoe *shirt) setLogo(logo string) {
	_shoe.logo = logo
}

func (_shoe *shirt) getLogo() string {
	return _shoe.logo
}

func (_shoe *shirt) setSize(size int) {
	_shoe.size = size
}

func (_shoe *shirt) getSize() int {
	return _shoe.size
}

// adidasShirt implements iShirt
type adidasShirt struct {
	shirt
}

// nikeShirt implements iShirt
type nikeShirt struct {
	shirt
}

// interface
type iSportsFactory interface {
	makeShoe() iShoe
	makeShirt() iShirt
}

func getSportsFactory(brand string) (iSportsFactory, error) {
	if brand == "adidas" {
		return &adidas{}, nil
	}
	if brand == "nike" {
		return &nike{}, nil
	}
	return nil, fmt.Errorf("wrong brand type passed")
}

// abstract factory - adidas implments iSportsFactory
type adidas struct{}

func (*adidas) makeShoe() iShoe {
	return &adidasShoe{
		shoe: shoe{
			logo: "adidas",
			size: 14,
		},
	}
}

func (*adidas) makeShirt() iShirt {
	return &adidasShirt{
		shirt: shirt{
			logo: "adidas",
			size: 28,
		},
	}
}

// abstract factory - nike implements iSportsFactory
type nike struct{}

func (*nike) makeShoe() iShoe {
	return &nikeShoe{
		shoe: shoe{
			logo: "nike",
			size: 14,
		},
	}
}

func (*nike) makeShirt() iShirt {
	return &nikeShirt{
		shirt: shirt{
			logo: "nike",
			size: 28,
		},
	}
}

func printShoeDetails(_shoe iShoe) {
	fmt.Printf("Logo: %s\n", _shoe.getLogo())
	fmt.Printf("Size: %d\n", _shoe.getSize())
}

func printShirtDetails(_shirt iShirt) {
	fmt.Printf("Logo: %s\n", _shirt.getLogo())
	fmt.Printf("Size: %d\n", _shirt.getSize())
}

func main() {
	adidasFactory, _ := getSportsFactory("adidas")
	nikeFactory, _ := getSportsFactory("nike")

	adidasShoe := adidasFactory.makeShoe()
	adidasShirt := adidasFactory.makeShirt()

	nikeShoe := nikeFactory.makeShoe()
	nikeShirt := nikeFactory.makeShirt()

	printShoeDetails(adidasShoe)
	printShirtDetails(adidasShirt)

	printShoeDetails(nikeShoe)
	printShirtDetails(nikeShirt)
}
