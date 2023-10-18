#pragma once
#include <QWidget>
#include <QBoxLayout>
#include <QPushButton>
#include "service.h"
#include <QTableWidget>
#include <QGroupBox>
#include "produs.h"
#include <QString>
#include <QStringList>
#include <QHeaderView>
#include <QLineEdit>
#include <QListWidget>
#include "observer.h"
#include <QPainter>

class CartWindow : public QWidget, public Observer {
private:
	Service& service;
	QTableWidget* allProdTable;
	QTableWidget* cartTable;

	QLineEdit* setNr;
	QLineEdit* setFile;
	QPushButton* emptyButton;
	QPushButton* randomButton;
	QPushButton* exportButton;

	QListWidget* list;
	void reloadList(vector<Produs>);

	void initializeCartComponents();
	void connectSignalsAndSlots();
	void reloadAllProducts(const vector<Produs>);
public:
	CartWindow(Service& serv) : service{ serv } {
		service.addObserver(this);
		initializeCartComponents();
		connectSignalsAndSlots();
		reloadAllProducts(service.get_all_cart_service());

		reloadList(service.get_all_cart_service());

	};

	void update() override {
		reloadList(service.get_all_cart_service());
	}

	~CartWindow() {
		service.removeObserver(this);
	}
};

class CartGUIDraw :public QWidget, public Observer {
private:
	Service& service;

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		int x = 0;
		int y = 0;
		for (const Produs& produs : service.get_all_cart_service()) {
			p.drawRect(x, y, 10, produs.get_pret() * 10);
			x += 40;
		}
	}

	void update() override {
		repaint();
	}

	~CartGUIDraw() {
		service.removeObserver(this);
	}

public:
	CartGUIDraw(Service& service) :service{ service } {
		service.addObserver(this);
	};
};
