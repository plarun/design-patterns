package main

import "fmt"

type pizza interface {
	getPrice() int
}

type veggieMania struct{}

func (item *veggieMania) getPrice() int {
	return 15
}

type tomatoTopping struct {
	pizza pizza
}

func (item *tomatoTopping) getPrice() int {
	price := item.pizza.getPrice()
	return price + 5
}

type cheeseTopping struct {
	pizza pizza
}

func (item *cheeseTopping) getPrice() int {
	price := item.pizza.getPrice()
	return price + 10
}

func showPrice(pizza pizza) {
	fmt.Println(pizza.getPrice())
}

func app() {
	pizza := &veggieMania{}
	pizzaWithCheese := &cheeseTopping{
		pizza: pizza,
	}
	pizzaWithTomato := &tomatoTopping{
		pizza: pizza,
	}
	pizzaWithCheeseAndTomato := &tomatoTopping{
		pizza: pizzaWithCheese,
	}

	showPrice(pizza)
	showPrice(pizzaWithCheese)
	showPrice(pizzaWithTomato)
	showPrice(pizzaWithCheeseAndTomato)
}

func main() {
	app()
}
