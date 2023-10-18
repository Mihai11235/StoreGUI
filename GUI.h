#pragma once
#include "service.h"
#include <QWidget>
#include <QPushButton>
#include <QBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QTableWidget>
#include <QStringList>
#include <QString>
#include "QMessageBox"

#include <QHeaderView>
#include <QGroupBox>
#include <QApplication>
#include <QStyleFactory>
#include <QRadioButton>
#include <QListWidget>
#include "TableModel.h"


using std::vector;
using std::string;

class GUIModel : public QWidget {
private:
	Service& service;

	QLineEdit* setId;
	QLineEdit* setName;
	QLineEdit* setType;
	QLineEdit* setManufacturer;
	QLineEdit* setPrice;

	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* modifyButton;
	QPushButton* darkButton;

	QLineEdit* searchById;
	QPushButton* searchButton;

	QRadioButton* priceFilterButton;
	QRadioButton* nameFilterButton;
	QRadioButton* manufacturerFilterButton;
	QLineEdit* setFilter;
	QPushButton* filterButton;

	QRadioButton* nameSortButton;
	QRadioButton* priceSortButton;
	QRadioButton* nameAndTypeSortButton;
	QPushButton* sortButton;

	QPushButton* undoButton;

	QTableWidget* table;

	QPushButton* reloadButton;


	QPushButton* cartButton;
	QPushButton* cartReadOnlyButton;
	QPushButton* addToCartButton;


	QListWidget* list;
	void InitializeGUIComponents();
	void ConnectSignalsAndSlots();
	void ReloadAllProducts(const vector<Produs>& all);
	void AddDynamicButtons();

	void addProductGUI();
	void deleteProductGUI();
	void modifyProductGUI();
	void searchProductGUI();
	void filterProductGUI();
	void sortProductGUI();
	void undoActionGUI();
	void addToCartGUI();

	void reloadList(vector<Produs> all);

	MyTableModel* model;
	QTableView* tableView;

public:
	GUIModel(Service& service) :service{ service } {
		QIcon iconMain("store-icon.png");
		this->setWindowIcon(iconMain);
		InitializeGUIComponents();
		ConnectSignalsAndSlots();
		ReloadAllProducts(service.get_all_service());
	}
};