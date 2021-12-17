package main

import (
	"fmt"
	"sync"
)

var lock = &sync.Mutex{}

type single struct{}

var singleInstance *single

func getInstance() *single {
	if singleInstance == nil {
		lock.Lock()
		defer lock.Unlock()

		if singleInstance == nil {
			fmt.Println("Creating instance")
			singleInstance = &single{}
		} else {
			fmt.Println("Instance already exists")
		}
	} else {
		fmt.Println("Instance already exists")
	}
	return singleInstance
}

func app() {
	for i := 0; i < 5; i++ {
		go getInstance()
	}
	fmt.Scanln()
}

func main() {
	app()
}
