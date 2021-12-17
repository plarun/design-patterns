package main

import "fmt"

// interface
type component interface {
	search(string)
}

// file implements component
type file struct {
	name string
}

func (_file *file) search(keyword string) {
	fmt.Printf("Searching for %s in file %s\n", keyword, _file.getName())
}

func (_file *file) getName() string {
	return _file.name
}

// folder implements component
type folder struct {
	components []component
	name       string
}

func (_folder *folder) search(keyword string) {
	fmt.Printf("Searching recursively for %s in folder %s\n", keyword, _folder.getName())
	for _, composite := range _folder.components {
		composite.search(keyword)
	}
}

func (_folder *folder) getName() string {
	return _folder.name
}

func (_folder *folder) add(comp component) {
	_folder.components = append(_folder.components, comp)
}

func app() {
	file1 := &file{name: "File1"}
	file2 := &file{name: "File2"}
	file3 := &file{name: "File3"}

	folder1 := &folder{
		name: "Folder1",
	}

	folder1.add(file1)

	folder2 := &folder{
		name: "Folder2",
	}
	folder2.add(file2)
	folder2.add(file3)
	folder2.add(folder1)

	folder2.search("rose")
}

func main() {
	app()
}
