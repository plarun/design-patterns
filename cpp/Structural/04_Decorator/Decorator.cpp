#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

/*
Type: Structural
Pattern: Decorator

Attach new behaviors to objects by placing these objects inside special wrapper objects that contain the behaviors.

Use the Decorator pattern when you need to be able to assign extra behaviors to objects at runtime without breaking the code that uses these objects.
Use the pattern when it’s awkward or not possible to extend an object’s behavior using inheritance.
*/

// interface
class DataSource {
public:
	virtual void writeData(std::string data) = 0;
	virtual std::string readData() = 0;
};

class FileDataSource : public DataSource {
private:
	std::string filename;

public:
	FileDataSource(std::string name) : filename(name) {}
	void writeData(std::string data) override {
		std::ofstream fout;
		fout.open(filename);
		fout << data;
		fout.close();
		std::cout << "write: " << data << std::endl;
	}
	std::string readData() override {
		std::string data, line;
		std::ifstream fin;
		fin.open(filename);
		fin >> line;
		data += line;
		fin.close();
		std::cout << "read: " << data << std::endl;
		return data;
	}
};

class DataSourceDecorator : public DataSource {
private:
	DataSource* wrappee;

public:
	DataSourceDecorator(DataSource* source) : wrappee(source) {}
	void writeData(std::string data) override {
		wrappee->writeData(data);
	}
	std::string readData() override {
		return wrappee->readData();
	}
};

class EncryptionDecorator : public DataSourceDecorator {
private:
	std::string encrypt(std::string data) {
		std::string cipherText;
		int key = 15;
		for (int c: data)
			cipherText += char((int(c+key-'a')%26)+'a');
		std::cout << "encrypt: " << cipherText << std::endl;
		return cipherText;
	}
	std::string decrypt(std::string data) {
		std::string normalText;
		int key = 15;
		for (char& c: data)
			normalText += char((int(c-key-'a')%26)+'a');
		std::cout << "decrypt: " << normalText << std::endl;
		return normalText;
	}
public:
	EncryptionDecorator(DataSource* source) : DataSourceDecorator(source) {}
	void writeData(std::string data) override {
		DataSourceDecorator::writeData(encrypt(data));
	}
	std::string readData() override {
		return decrypt(DataSourceDecorator::readData());
	}
};

class CompressionDecorator : public DataSourceDecorator {
private:
	std::string compress(std::string data) {
		std::string compressedText;
		if (data.size()) {
			for (int i=1, count=0, curr=data[0]; i<=data.size(); ++i) {
				if (i == data.size() || curr != data[i]) {
					if (count > 0) compressedText += std::to_string(count+1);
					compressedText += curr;
					curr = data[i];
					count = 0;
				} else {
					++count;
				}
			}
		}
		std::cout << "compress: " << compressedText << std::endl;
		return compressedText.size() < data.size() ? compressedText : data;
	}
	std::string decompress(std::string data) {
		std::string normalText;
		std::string::size_type sz;
		if (data.size()) {
			std::string num;
			for (char& c: data) {
				if (c-'0' >= 0 && c-'0' <= 9)
					num += c;
				else {
					int n = std::stoi(num, &sz);
					n = n == 0 ? 1 : n;
					for (int i=0; i<n; ++i) normalText += c;
					num = "0";
				}
			}
		}
		std::cout << "decompress: " << normalText << std::endl;
		return normalText;
	}

public:
	CompressionDecorator(DataSource* source) : DataSourceDecorator(source) {}
	void writeData(std::string data) override {
		DataSourceDecorator::writeData(compress(data));
	}
	std::string readData() override {
		return decompress(DataSourceDecorator::readData());
	}
};

void app() {
	std::string data = "aabbbcdddeff";

	DataSource* f1 = new FileDataSource("f1.txt");
	DataSource* f2 = new FileDataSource("f2.txt");
	DataSource* f3 = new FileDataSource("f3.txt");
	DataSource* f4 = new FileDataSource("f4.txt");

	// plain
	f1->writeData(data);
	std::cout << f1->readData() << "\n\n";
	delete f1;

	// compression
	DataSourceDecorator* comp = new CompressionDecorator(f2);
	comp->writeData(data);
	std::cout << comp->readData() << "\n\n";
	delete f2;

	// Encryption
	DataSource* enc = new EncryptionDecorator(f3);
	enc->writeData(data);
	std::cout << enc->readData() << "\n\n";
	delete f3;

	DataSourceDecorator* full = new EncryptionDecorator(new CompressionDecorator(f4));
	full->writeData(data);
	std::cout << full->readData();
}

int main () {
	app();
}