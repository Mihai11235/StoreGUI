#pragma once
#include <vector>

using std::vector;

class Observer {
public:
	virtual void update() = 0;
};

class Observable {
	vector<Observer*> observers;
public:
	void addObserver(Observer* observer) {
		observers.push_back(observer);
	}

	void removeObserver(Observer* observer) {
		observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
	}

	void notify() {
		for (Observer*& obs : observers) {
			obs->update();
		}
	}
};