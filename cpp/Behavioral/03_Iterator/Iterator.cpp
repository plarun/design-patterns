#include <iostream>
#include <string>
#include <vector>

/*
Type: Behavioural
Pattern: Iterator

lets you traverse elements of a collection without exposing its underlying representation (list, stack, tree, etc.).


*/

template <typename T, typename U>
class Iterator {
	private:
		U* container;
		typename std::vector<T>::iterator iter;

	public:
		Iterator(U* _data, bool reverse=false) : iterData(_data) {
			iter = container->dataList.begin();
		}

		void first() {
			iter = container->dataList.begin();
		}

		void next() {
			iter++;
		}

		bool isDone() {
			return iter == container->dataList.end();
		}

		typename std::vector<T>::iterator current() {
			return iter;
		}
};

template <class T>
class Container {
	private:
		typename std::vector<T> dataList;
		friend class Iterator<T, Container>;

	public:
		void add(T val) {
			dataList.push_back(val);
		}

		Iterator<T, Container>* createIterator() {
			return new Iterator<T, Container>(this);
		}
};

class Data {
	private:
		int data;
	
	public:
		Data(int _data=0) : data(_data) {}

		void setData(int _data) {
			data = _data;
		}

		int getData() {
			return data;
		}
};

void app() {
	Container<int> intContainer;
	for (int i=0; i<10; ++i) intContainer.add(i);

	Iterator<int, Container<int>>* intIter = intContainer.createIterator();
	for (intIter->first(); !intIter->isDone(); intIter->next())
		std::cout << *intIter->current() << "\n";
	
	Container<Data> dataContainer;
	Data a(100), b(1000), c(10000);
	dataContainer.add(a);
	dataContainer.add(b);
	dataContainer.add(c);

	Iterator<Data, Container<Data>>* dataIter = dataContainer.createIterator();
	for (dataIter->first(); !dataIter->isDone(); dataIter->next())
		std::cout << dataIter->current()->getData() << "\n";
	
	delete intIter;
	delete dataIter;
}

int main() {
	app();
}