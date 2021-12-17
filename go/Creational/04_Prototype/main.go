package main

import "fmt"

// interface
type inode interface {
	print(string)
	clone() inode
}

// file implements inode
type file struct {
	name string
}

func (_file *file) print(indentation string) {
	fmt.Println(indentation + "+ " + _file.name)
}

func (_file *file) clone() inode {
	return &file{
		name: _file.name + "_clone",
	}
}

// folder implements inode
type folder struct {
	children []inode
	name     string
}

func (_folder *folder) print(indentation string) {
	fmt.Println(indentation + "+ " + _folder.name)
	for _, child := range _folder.children {
		child.print(indentation + indentation)
	}
}

func (_folder *folder) clone() inode {
	var tmpChildren []inode
	for _, child := range _folder.children {
		childCopy := child.clone()
		tmpChildren = append(tmpChildren, childCopy)
	}
	cloneFolder := &folder{
		name:     _folder.name + "_clone",
		children: tmpChildren,
	}
	return cloneFolder
}

func app() {
	file1 := &file{name: "file1"}
	file2 := &file{name: "file2"}
	file3 := &file{name: "file3"}

	folder1 := &folder{
		children: []inode{file1},
		name:     "folder1",
	}
	folder2 := &folder{
		children: []inode{folder1, file2, file3},
		name:     "folder2",
	}

	folder2.print("  ")

	cloneFolder := folder2.clone()
	cloneFolder.print("  ")
}

func main() {
	app()
}
