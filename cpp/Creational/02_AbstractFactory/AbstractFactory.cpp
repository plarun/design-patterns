#include <iostream>

/*
Type: Creational
Pattern: Abstract Factory

When your code needs to work with various families of related products, 
but you don’t want it to depend on the concrete classes of those products—they might be unknown beforehand 
or you simply want to allow for future extensibility.

Button and its concrete classes are product
Checkbox and its concrete classes are product
Here various families are windows and mac

We can easily add new family (linux) for products(button, checkbox)
App dont know about Concrete classess of product
*/

// interface
class Button {
	public:
	virtual void render() = 0;
};

class WindowsButton : public Button {
	public:
	void render() override {
		std::cout << "Windows button rendered\n";
	}
};

class MacButton : public Button {
	public:
	void render() override {
		std::cout << "Mac button rendered\n";
	}
};

// interface
class Checkbox {
	public:
	virtual void render() = 0;
};

class WindowsCheckbox : public Checkbox {
	public:
	void render() override {
		std::cout << "Windows checkbox rendered\n";
	}
};

class MacCheckbox : public Checkbox {
	public:
	void render() override {
		std::cout << "Mac checkbox rendered\n";
	}
};

// interface
class GUIFactory {
	public:
	virtual Button* createButton() = 0;
	virtual Checkbox* createCheckbox() = 0;
};

class WindowsGUIFactory : public GUIFactory {
	public:
	Button* createButton() override {
		return new WindowsButton();
	}
	Checkbox* createCheckbox() override {
		return new WindowsCheckbox();
	}
};

class MacGUIFactory : public GUIFactory {
	public:
	Button* createButton() override {
		return new MacButton();
	}
	Checkbox* createCheckbox() override {
		return new MacCheckbox();
	}
};

class App {
	private:
	GUIFactory* gui;
	Button* button;
	Checkbox* checkbox;

	public:
	App(GUIFactory* guiFactory) : gui(guiFactory) {}
	void setButton() {
		this->button = gui->createButton();
	}
	void setCheckbox() {
		this->checkbox = gui->createCheckbox();
	}
	void renderButton() {
		this->button->render();
	}
	void renderCheckbox() {
		this->checkbox->render();
	}
};

void app(std::string os) {
	GUIFactory* factory;

	if (os == "Windows")
		factory = new WindowsGUIFactory();
	else if (os == "Mac")
		factory = new MacGUIFactory();
	else
		throw std::invalid_argument("os should be either Windows or Mac");

	App* guiApp = new App(factory);
	guiApp->setButton();
	guiApp->setCheckbox();
	guiApp->renderButton();
	guiApp->renderCheckbox();
	delete guiApp;
}

int main() {
	app("Windows");
	app("Mac");
}