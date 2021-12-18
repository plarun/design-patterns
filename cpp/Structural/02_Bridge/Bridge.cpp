#include <iostream>

/*
Type: Structural
Pattern: Bridge

Split a large class or a set of closely related classes into two separate
hierarchies—abstraction and implementation—which can be developed independently of each other.

Here we can control a device with multiple remotes
Use the Bridge pattern when you want to divide and organize a monolithic class that has several variants of some functionality 
	(for example, if the class can work with various database servers).
Use the pattern when you need to extend a class in several orthogonal (independent) dimensions.
Use the Bridge if you need to be able to switch implementations at runtime.
*/

// interface
class Device {

public:
	virtual bool isEnabled() = 0;
	virtual void enable() = 0;
	virtual void disable() = 0;
	virtual int getVolume() = 0;
	virtual void setVolume(int percent) = 0;
	virtual int getChannel() = 0;
	virtual void setChannel(int channel) = 0;
	virtual void printStatus() = 0;
};

class Radio : public Device {
private:
	bool on;
	int volume;
	int channel;

public:
	Radio() : on(false), volume(10), channel(1) {}
	bool isEnabled() override {
		return on;
	}
	void enable() override {
		on = true;
	}
	void disable() override {
		on = false;
	}
	int getVolume() override {
		return volume;
	}
	void setVolume(int vol) override {
		if (vol < 0) volume = 0;
		else if (vol > 100) volume = 100;
		else volume = vol;
	}
	int getChannel() override {
		return channel;
	}
	void setChannel(int channel_) override {
		channel = channel_;
	}
	void printStatus() override {
		std::cout << "Radio: " << (on ? "On" : "Off") << ' ' << volume << ' ' << channel << std::endl;
	}
};

class Television : public Device {
private:
	bool on;
	int volume;
	int channel;

public:
	Television() : on(false), volume(10), channel(1) {}
	bool isEnabled() override {
		return on;
	}
	void enable() override {
		on = true;
	}
	void disable() override {
		on = false;
	}
	int getVolume() override {
		return volume;
	}
	void setVolume(int vol) override {
		if (vol < 0) volume = 0;
		else if (vol > 100) volume = 100;
		else volume = vol;
	}
	int getChannel() override {
		return channel;
	}
	void setChannel(int channel_) override {
		channel = channel_;
	}
	void printStatus() override {
		std::cout << "Television: " << (on ? "On" : "Off") << ' ' << volume << ' ' << channel << std::endl;
	}
};

// interface
class Remote {
	virtual void power() = 0;
	virtual void volumeDown() = 0;
	virtual void volumeUp() = 0;
	virtual void channelDown() = 0;
	virtual void channelUp() = 0;
};

class BasicRemote : public Remote {
protected:
	Device* device;

public:
	BasicRemote() {}
	BasicRemote(Device* device_) : device(device_) {}
	void power() override {
		if (device->isEnabled()) device->disable();
		else device->enable();
	}
	void volumeDown() override {
		device->setVolume(device->getVolume() - 1);
	}
	void volumeUp() override {
		device->setVolume(device->getVolume() + 1);
	}
	void channelDown() override {
		device->setChannel(device->getChannel() - 1);
	}
	void channelUp() override {
		device->setChannel(device->getChannel() + 1);
	}
};

class AdvancedRemote : public BasicRemote {
public:
	AdvancedRemote(Device* device) : BasicRemote(device) {}
	void mute() {
		device->setVolume(0);
	}
};

void app(Device* device) {
	BasicRemote* basicRemote = new BasicRemote(device);
	basicRemote->power();
	basicRemote->volumeUp();
	basicRemote->channelUp();
	device->printStatus();
	delete basicRemote;

	AdvancedRemote* advancedRemote = new AdvancedRemote(device);
	advancedRemote->power();
	advancedRemote->volumeUp();
	advancedRemote->channelUp();
	advancedRemote->mute();
	device->printStatus();
	delete advancedRemote;
}

int main() {
	Television* tv = new Television();
	Radio* radio = new Radio();

	app(tv);
	app(radio);

	delete tv;
	delete radio;
}