package main

import "fmt"

type user struct {
	name string
	age  int
}

// iterator interface
type iterator interface {
	hasNext() bool
	getNext() *user
}

// userIterator implements iterator
type userIterator struct {
	index int
	users []*user
}

func (userIter *userIterator) hasNext() bool {
	return userIter.index < len(userIter.users)
}

func (userIter *userIterator) getNext() *user {
	if userIter.hasNext() {
		user := userIter.users[userIter.index]
		userIter.index++
		return user
	}
	return nil
}

// collection interface
type collection interface {
	createIterator() iterator
}

// userCollection implements collection
type userCollection struct {
	users []*user
}

func (userColl *userCollection) createIterator() iterator {
	return &userIterator{
		users: userColl.users,
	}
}

func app() {
	user1 := &user{
		name: "Arun",
		age:  20,
	}
	user2 := &user{
		name: "Admin",
		age:  40,
	}

	var userCollection collection = &userCollection{
		users: []*user{user1, user2},
	}

	iterator := userCollection.createIterator()
	for iterator.hasNext() {
		user := iterator.getNext()
		fmt.Printf("Name: %s\tAge: %d\n", user.name, user.age)
	}
}

func main() {
	app()
}
