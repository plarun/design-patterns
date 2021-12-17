package main

import "fmt"

type house struct {
	windowType string
	doorType   string
	floor      int
}

// interface
type iBuilder interface {
	setWindowType()
	setDoorType()
	setNumFloor()
	getHouse() house
}

// normalBuilder implements iBuilder
type normalBuilder struct {
	windowType string
	doorType   string
	floor      int
}

func newNormalBuilder() *normalBuilder {
	return &normalBuilder{}
}

func (builder *normalBuilder) setWindowType() {
	builder.windowType = "Wooden window"
}

func (builder *normalBuilder) setDoorType() {
	builder.doorType = "Wooden door"
}

func (builder *normalBuilder) setNumFloor() {
	builder.floor = 2
}

func (builder *normalBuilder) getHouse() house {
	return house{
		windowType: builder.windowType,
		doorType:   builder.doorType,
		floor:      builder.floor,
	}
}

// iglooBuilder implements iBuilder
type iglooBuilder struct {
	windowType string
	doorType   string
	floor      int
}

func newIglooBuilder() *iglooBuilder {
	return &iglooBuilder{}
}

func (builder *iglooBuilder) setWindowType() {
	builder.windowType = "Ice window"
}

func (builder *iglooBuilder) setDoorType() {
	builder.doorType = "Ice door"
}

func (builder *iglooBuilder) setNumFloor() {
	builder.floor = 1
}

func (builder *iglooBuilder) getHouse() house {
	return house{
		windowType: builder.windowType,
		doorType:   builder.doorType,
		floor:      builder.floor,
	}
}

func getBuilder(builderType string) iBuilder {
	if builderType == "normal" {
		return newNormalBuilder()
	}
	if builderType == "igloo" {
		return newIglooBuilder()
	}
	return nil
}

type director struct {
	builder iBuilder
}

func newDirector() *director {
	return &director{
		builder: nil,
	}
}

func (dir *director) setBuilder(builder iBuilder) {
	dir.builder = builder
}

func (dir *director) buildHouse() house {
	dir.builder.setWindowType()
	dir.builder.setDoorType()
	dir.builder.setNumFloor()
	return dir.builder.getHouse()
}

func app(houseType string) {
	builder := getBuilder(houseType)

	director := newDirector()
	director.setBuilder(builder)

	house := director.buildHouse()

	fmt.Printf("House window: %s\n", house.windowType)
	fmt.Printf("House door: %s\n", house.doorType)
	fmt.Printf("House floor: %d\n", house.floor)
}

func main() {
	app("normal")
	app("igloo")
}
