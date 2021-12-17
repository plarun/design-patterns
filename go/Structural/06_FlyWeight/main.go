package main

import "fmt"

const (
	AttackerDressType = "Attacker Dress"
	DefenderDressType = "Defender Dress"
)

// interface
type dress interface {
	getColor() string
}

type attackerDress struct {
	color string
}

func (_attackerDress *attackerDress) getColor() string {
	return _attackerDress.color
}

func newAttackerDress() *attackerDress {
	return &attackerDress{color: "red"}
}

type defenderDress struct {
	color string
}

func (_defenderDress *defenderDress) getColor() string {
	return _defenderDress.color
}

func newDefenderDress() *defenderDress {
	return &defenderDress{color: "blue"}
}

var dressFactorySingleInstance = &dressFactory{
	dressMap: make(map[string]dress),
}

type dressFactory struct {
	dressMap map[string]dress
}

func (_dressFactory *dressFactory) getDressByType(dressType string) (dress, error) {
	if _dressFactory.dressMap[dressType] != nil {
		return _dressFactory.dressMap[dressType], nil
	}
	if dressType == AttackerDressType {
		_dressFactory.dressMap[dressType] = newAttackerDress()
		return _dressFactory.dressMap[dressType], nil
	}
	if dressType == DefenderDressType {
		_dressFactory.dressMap[dressType] = newDefenderDress()
		return _dressFactory.dressMap[dressType], nil
	}
	return nil, fmt.Errorf("wrong dress type passed")
}

func getDressFactorySingleInstance() *dressFactory {
	return dressFactorySingleInstance
}

type player struct {
	dress      dress
	playerType string // either A or D
	lat        int
	long       int
}

func newPlayer(playerType, dressType string) *player {
	dress, _ := getDressFactorySingleInstance().getDressByType(dressType)
	return &player{
		playerType: playerType,
		dress:      dress,
		lat:        0,
		long:       0,
	}
}

type game struct {
	attackers []*player
	defenders []*player
}

func newGame() *game {
	return &game{
		attackers: make([]*player, 1),
		defenders: make([]*player, 1),
	}
}

func (_game *game) addAttacker(dressType string) {
	player := newPlayer("A", dressType)
	_game.attackers = append(_game.attackers, player)
}

func (_game *game) addDefender(dressType string) {
	player := newPlayer("D", dressType)
	_game.defenders = append(_game.defenders, player)
}

func app() {
	game := newGame()

	game.addAttacker(AttackerDressType)
	game.addAttacker(AttackerDressType)
	game.addAttacker(AttackerDressType)
	game.addAttacker(AttackerDressType)

	game.addDefender(DefenderDressType)
	game.addDefender(DefenderDressType)
	game.addDefender(DefenderDressType)
	game.addDefender(DefenderDressType)

	dressFactoryInstance := getDressFactorySingleInstance()

	for dressType, dress := range dressFactoryInstance.dressMap {
		fmt.Printf("DressColorType: %s\nDressColor: %s\n", dressType, dress.getColor())
	}
}

func main() {
	app()
}
