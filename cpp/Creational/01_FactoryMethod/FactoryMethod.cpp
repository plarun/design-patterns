#include <iostream>

/*
Type: Creational pattern
Pattern: Factory method

It provides an interface for creating objects in a superclass, but allows subclasses to alter the type of objects that will be created.

Use the Factory Method when you don’t know beforehand the exact types and dependencies of the objects your code should work with.
Use the Factory Method when you want to provide users of your library or framework with a way to extend its internal components.
Use the Factory Method when you want to save system resources by reusing existing objects instead of rebuilding them each time.

Button and its concrete classes are product
Dialog and its concrete classes are creator
We dont know about concrete classes (WindowsButton, WebButton).
We can assume the product as third party
*/

// interface
class Button {
	public:
	virtual void render() = 0;
	virtual void onClick() = 0;
};

class WindowsButton : public Button {
	public:
	void render() {
		std::cout << "Rendering windows button\n";
	}
	void onClick() {
		std::cout << "Windows click event\n";
	}
};

class WebButton : public Button {
	public:
	void render() {
		std::cout << "Rendering web button\n";
	}
	void onClick() {
		std::cout << "Web click event\n";
	}
};

// abstract
class Dialog {
	public:
	virtual Button* createButton() = 0;
};

class WindowsDialog : public Dialog {
	public:
	Button* createButton() override {
		return new WindowsButton();
	}
};

class WebDialog : public Dialog {
	public:
	Button* createButton() override {
		return new WebButton();
	}
};

void app(std::string sys) {
	Dialog* dialog;

	if (sys == "Windows")
		dialog = new WindowsDialog();
	else if (sys == "Web")
		dialog = new WebDialog();
	else
		throw std::invalid_argument("sys type should be either windows or web");
	
	Button* button = dialog->createButton();
	button->onClick();
	button->render();

	delete dialog;
	delete button;
}

int main() {
	app("Windows");
	app("Web");
}