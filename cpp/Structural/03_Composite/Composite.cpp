#include <iostream>
#include <algorithm>
#include <list>
#include <string>

/*
Type: Structural
Pattern: Composite

Compose objects into tree structures and then work with these structures as if they were individual objects.

Use the Composite pattern when you have to implement a tree-like object structure.
Use the pattern when you want the client code to treat both simple and complex elements uniformly.
*/

// abstract
class Component {
protected:
	Component* parent;

public:
	virtual ~Component() {}
	void setParent(Component* newParent) {
		parent = newParent;
	}
	Component* getParent() const {
		return parent;
	}
	virtual void add(Component* component) {}
	virtual void remove(Component* component) {}
	virtual bool isComposite() const {
		return false;
	}
	virtual std::string operation() const = 0;
};

class Leaf : public Component {
public:
	std::string operation() const {
		return "Leaf";
	}
};

class Composite : public Component {
protected:
	std::list<Component*> children;

public:
	void add(Component* component) override {
		children.push_back(component);
		component->setParent(this);
	}
	void remove(Component* component) override {
		children.remove(component);
		component->setParent(nullptr);
	}
	bool isComposite() const {
		return true;
	}
	std::string operation() const override {
		std::string result;
		for (const Component* comp: children)
			result += comp == *children.begin() ? comp->operation() : " + " + comp->operation();
		return "Branch ( " + result + " )";
	}
};

void print(Component* component) {
	std::cout << component->operation() << "\n\n";
}

void link(Component* comp1, Component* comp2) {
	if (comp1->isComposite())
		comp1->add(comp2);
	print(comp1);
}

void app() {
	Component* simple = new Leaf;
	print(simple);

	Component* tree = new Composite;
	Component* branch1 = new Composite;
	Component* branch2 = new Composite;
	Component* leaf1 = new Leaf;
	Component* leaf2 = new Leaf;
	Component* leaf3 = new Leaf;

	branch1->add(leaf1);
	branch1->add(leaf2);
	branch2->add(leaf3);

	tree->add(branch1);
	tree->add(branch2);

	print(tree);
	link(tree, simple);

	delete simple;
	delete tree;
	delete branch1;
	delete branch2;
	delete leaf1;
	delete leaf2;
	delete leaf3;
}

int main() {
	app();
}