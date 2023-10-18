#include "cart.h"
#include <QFormLayout>
#include <QMessageBox>

void CartWindow::initializeCartComponents() {
	QHBoxLayout* mainLy = new QHBoxLayout;
	this->setLayout(mainLy);

	QVBoxLayout* leftLy = new QVBoxLayout;
	mainLy->addLayout(leftLy);
	QVBoxLayout* rightLy = new QVBoxLayout;
	mainLy->addLayout(rightLy);

	QGroupBox* leftBox = new QGroupBox;
	leftLy->addWidget(leftBox);
	QGroupBox* rightBox = new QGroupBox;
	rightLy->addWidget(rightBox);

	QVBoxLayout* leftBoxLy = new QVBoxLayout;
	leftBox->setLayout(leftBoxLy);
	QVBoxLayout* rightBoxLy = new QVBoxLayout;
	rightBox->setLayout(rightBoxLy);


	QGroupBox* emptyBox = new QGroupBox;
	leftBoxLy->addWidget(emptyBox);

	QHBoxLayout* emptyBoxLy = new QHBoxLayout;
	emptyBox->setLayout(emptyBoxLy);

	QGroupBox* randomBox = new QGroupBox;
	leftBoxLy->addWidget(randomBox);

	QVBoxLayout* randomBoxLy = new QVBoxLayout;
	randomBox->setLayout(randomBoxLy);

	QGroupBox* exportBox = new QGroupBox;
	leftBoxLy->addWidget(exportBox);

	QVBoxLayout* exportBoxLy = new QVBoxLayout;
	exportBox->setLayout(exportBoxLy);

	setNr = new QLineEdit;
	QFormLayout* randomLy = new QFormLayout;
	randomBoxLy->addLayout(randomLy);

	randomLy->addRow("Number of products:", setNr);

	setFile = new QLineEdit;
	QFormLayout* exportLy = new QFormLayout;
	exportBoxLy->addLayout(exportLy);

	exportLy->addRow("Name of file:", setFile);

	int noLines = 10;
	int noColums = 5;
	cartTable = new QTableWidget{ noLines, noColums };
	//ightBoxLy->addWidget(cartTable);
	list = new QListWidget;
	rightBoxLy->addWidget(list);

	QStringList header;
	header << "Barcode" << "Name" << "Type" << "Manufacturer" << "Price($)";
	this->cartTable->setHorizontalHeaderLabels(header);
	this->cartTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	cartTable->horizontalHeader()->setStretchLastSection(true); //stretch the last column


	emptyButton = new QPushButton{ "Empty cart" };
	emptyBoxLy->addWidget(emptyButton);
	randomButton = new QPushButton{ "Add random items to cart" };
	randomBoxLy->addWidget(randomButton);
	exportButton = new QPushButton{ "Export to file" };
	exportBoxLy->addWidget(exportButton);


}

void CartWindow::connectSignalsAndSlots() {
	QObject::connect(emptyButton, &QPushButton::clicked, [this]() {
		service.goleste_cart_service();
		reloadAllProducts(service.get_all_cart_service());
		reloadList(service.get_all_cart_service());
		});

	QObject::connect(randomButton, &QPushButton::clicked, [this]() {
		int nr = setNr->text().toInt();
		setNr->clear();
		service.genereaza_cart_service(nr);
		reloadAllProducts(service.get_all_cart_service());
		reloadList(service.get_all_cart_service());
		});

	QObject::connect(exportButton, &QPushButton::clicked, [this]() {
		try {
			string file = setFile->text().toStdString();
			setNr->clear();
			service.export_cart_service(file);
		}
		catch (CartError& ce) {
			QMessageBox::warning(this, "Export Cart Warning", QString::fromStdString(string(ce)));
		}
		});
}

void CartWindow::reloadAllProducts(vector<Produs> all) {

	cartTable->clearContents();
	cartTable->setRowCount(all.size());

	int rowNumber = 0;
	for (const Produs& p : all) {
		cartTable->setItem(rowNumber, 0, new QTableWidgetItem{ QString::fromStdString(p.get_id()) });
		cartTable->setItem(rowNumber, 1, new QTableWidgetItem{ QString::fromStdString(p.get_nume()) });
		cartTable->setItem(rowNumber, 2, new QTableWidgetItem{ QString::fromStdString(p.get_tip()) });
		cartTable->setItem(rowNumber, 3, new QTableWidgetItem{ QString::fromStdString(p.get_producator()) });
		cartTable->setItem(rowNumber, 4, new QTableWidgetItem{ QString::number(p.get_pret()) });
		rowNumber++;
	}
}

void CartWindow::reloadList(vector<Produs> all) {
	list->clear();
	for (const Produs& p : all) {
		QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(p.get_nume()), list);
		item->setData(Qt::UserRole, QString::fromStdString(p.get_id()));
		item->setData(Qt::UserRole, QString::fromStdString(p.get_tip()));
		item->setData(Qt::UserRole, QString::fromStdString(p.get_producator()));
		item->setData(Qt::UserRole, QString::number(p.get_pret()));
	}
}

