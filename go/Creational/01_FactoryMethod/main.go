package main

import "fmt"

// Product interface
type igun interface {
	setName(name string)
	setPower(power int)
	getName() string
	getPower() int
}

// Concrete Product
type gun struct {
	name  string
	power int
}

func (gunObj *gun) setName(name string) {
	gunObj.name = name
}

func (gunObj *gun) getName() string {
	return gunObj.name
}

func (gunObj *gun) setPower(power int) {
	gunObj.power = power
}

func (gunObj *gun) getPower() int {
	return gunObj.power
}

// aggregate
type ak47 struct {
	gun
}

// ak47 gun factory method
func newAk47() igun {
	return &ak47{
		gun: gun{
			name:  "AK47 gun",
			power: 4,
		},
	}
}

// aggregate
type musket struct {
	gun
}

// musket gun factory method
func newMusket() igun {
	return &musket{
		gun: gun{
			name:  "Musket gun",
			power: 1,
		},
	}
}

func getGun(gunType string) (igun, error) {
	if gunType == "ak47" {
		return newAk47(), nil
	}
	if gunType == "musket" {
		return newMusket(), nil
	}
	return nil, fmt.Errorf("wrong gun type passed")
}

func printDetails(gunObj igun) {
	if gunObj == nil {
		return
	}
	fmt.Printf("Gun: %s\n", gunObj.getName())
	fmt.Printf("Power: %d\n", gunObj.getPower())
}

func main() {
	ak47, _ := getGun("ak47")
	musket, _ := getGun("musket")

	printDetails(ak47)
	printDetails(musket)
}
