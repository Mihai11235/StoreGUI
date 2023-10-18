#include "GUI.h"
#include "cart.h"


void GUIModel::InitializeGUIComponents() {
	QHBoxLayout* mainLy = new QHBoxLayout;
	this->setLayout(mainLy);


	//left side
	QVBoxLayout* leftLy = new QVBoxLayout;
	mainLy->addLayout(leftLy);


	QGroupBox* commandsBox = new QGroupBox{ "Commands" };
	leftLy->addWidget(commandsBox);

	QVBoxLayout* mainLeftBoxLy = new QVBoxLayout;
	commandsBox->setLayout(mainLeftBoxLy);


	//add, modify, delete
	QGroupBox* operationsBox = new QGroupBox{ "Operations" };
	QFormLayout* formLy = new QFormLayout;
	operationsBox->setLayout(formLy);
	mainLeftBoxLy->addWidget(operationsBox);

	setId = new QLineEdit;
	setName = new QLineEdit;
	setType = new QLineEdit;
	setManufacturer = new QLineEdit;
	setPrice = new QLineEdit;

	formLy->addRow(new QLabel{ "Product Id: " }, setId);
	formLy->addRow(new QLabel{ "Product Name: " }, setName);
	formLy->addRow(new QLabel{ "Product Type: " }, setType);
	formLy->addRow(new QLabel{ "Product Manufacturer: " }, setManufacturer);
	formLy->addRow(new QLabel{ "Product Price: " }, setPrice);

	QWidget* buttons = new QWidget;
	QHBoxLayout* buttonsLy = new QHBoxLayout;
	buttons->setLayout(buttonsLy);

	//formLy->addWidget(buttons);
	formLy->addWidget(buttons);

	addButton = new QPushButton{ "Add product" };
	buttonsLy->addWidget(addButton);
	deleteButton = new QPushButton{ "Delete product" };
	buttonsLy->addWidget(deleteButton);
	modifyButton = new QPushButton{ "Modify product" };
	buttonsLy->addWidget(modifyButton);



	//search
	searchById = new QLineEdit;
	QFormLayout* searchFormLy = new QFormLayout;
	searchFormLy->addRow("Product's id: ", searchById);
	searchButton = new QPushButton("🔍Search product");
	searchFormLy->addWidget(searchButton);

	QGroupBox* searchBox = new QGroupBox{ "Search" };
	searchBox->setLayout(searchFormLy);
	mainLeftBoxLy->addWidget(searchBox);

	//filter
	QGroupBox* filterBox = new QGroupBox{ "Filter" };
	mainLeftBoxLy->addWidget(filterBox);

	QFormLayout* filterFormLy = new QFormLayout;
	filterBox->setLayout(filterFormLy);

	QHBoxLayout* filterButtonsLy = new QHBoxLayout;
	filterFormLy->addRow(filterButtonsLy);

	priceFilterButton = new QRadioButton{ "Price" };
	nameFilterButton = new QRadioButton{ "Name" };
	manufacturerFilterButton = new QRadioButton{ "Manufacturer" };

	filterButtonsLy->addWidget(priceFilterButton);
	filterButtonsLy->addWidget(nameFilterButton);
	filterButtonsLy->addWidget(manufacturerFilterButton);

	setFilter = new QLineEdit;
	filterFormLy->addRow("Filter:            ", setFilter);

	filterButton = new QPushButton("Filter products");
	filterFormLy->addWidget(filterButton);

	//sort
	QGroupBox* sortBox = new QGroupBox{ "Sort" };
	mainLeftBoxLy->addWidget(sortBox);

	QVBoxLayout* sortLy = new QVBoxLayout;
	sortBox->setLayout(sortLy);

	QHBoxLayout* sortButtonsLy = new QHBoxLayout;
	sortLy->addLayout(sortButtonsLy);

	nameSortButton = new QRadioButton{ "Name" };
	priceSortButton = new QRadioButton{ "Price" };
	nameAndTypeSortButton = new QRadioButton{ "Name and Type" };

	sortButtonsLy->addWidget(nameSortButton);
	sortButtonsLy->addWidget(priceSortButton);
	sortButtonsLy->addWidget(nameAndTypeSortButton);

	sortButton = new QPushButton{ "Sort products" };
	sortLy->addWidget(sortButton);


	//reload and undo
	QGroupBox* otherBox = new QGroupBox{ "Other Operations" };
	mainLeftBoxLy->addWidget(otherBox);

	QHBoxLayout* otherButtons = new QHBoxLayout;
	otherBox->setLayout(otherButtons);

	reloadButton = new QPushButton{ "Reload all products" };
	otherButtons->addWidget(reloadButton);

	undoButton = new QPushButton{ "Undo" };
	otherButtons->addWidget(undoButton);

	undoButton->setShortcut(QKeySequence(tr("Ctrl+Z")));
	//undoButton->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z));

	//darkButton = new QPushButton("dark");
	//leftLy->addWidget(darkButton);


//right side
	QVBoxLayout* rightLy = new QVBoxLayout;
	mainLy->addLayout(rightLy);

	QGroupBox* rightBox = new QGroupBox;
	rightLy->addWidget(rightBox);

	QVBoxLayout* mainRightBoxLy = new QVBoxLayout;
	rightBox->setLayout(mainRightBoxLy);

	//visualising products
	QGroupBox* allProductsBox = new QGroupBox{ "All products" };
	mainRightBoxLy->addWidget(allProductsBox);

	QVBoxLayout* allProductsBoxLy = new QVBoxLayout;
	allProductsBox->setLayout(allProductsBoxLy);


	int noLines = 10;
	int noColums = 5;
	table = new QTableWidget{ noLines, noColums };
	table->setSelectionBehavior(QAbstractItemView::SelectRows);

	tableView = new QTableView;
	model = new MyTableModel{ service.get_all_service() };
	tableView->setModel(model);

	allProductsBoxLy->addWidget(tableView);
	tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	tableView->horizontalHeader()->setStretchLastSection(true); //stretch the last column


	QStringList header;
	header << "Barcode" << "Name" << "Type" << "Manufacturer" << "Price($)";
	table->setHorizontalHeaderLabels(header);
	table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
	table->horizontalHeader()->setStretchLastSection(true); //stretch the last column

	addToCartButton = new QPushButton{ "Add to cart" };
	mainRightBoxLy->addWidget(addToCartButton);

	cartButton = new QPushButton{ "Go to Cart" };
	mainRightBoxLy->addWidget(cartButton);

	cartReadOnlyButton = new QPushButton{ "Go to ReadOnly Cart" };
	mainRightBoxLy->addWidget(cartReadOnlyButton);

}

void GUIModel::ConnectSignalsAndSlots() {
	QObject::connect(addButton, &QPushButton::clicked, this, &GUIModel::addProductGUI);

	QObject::connect(deleteButton, &QPushButton::clicked, this, &GUIModel::deleteProductGUI);

	QObject::connect(modifyButton, &QPushButton::clicked, this, &GUIModel::modifyProductGUI);

	QObject::connect(searchButton, &QPushButton::clicked, this, &GUIModel::searchProductGUI);

	QObject::connect(filterButton, &QPushButton::clicked, this, &GUIModel::filterProductGUI);

	QObject::connect(sortButton, &QPushButton::clicked, this, &GUIModel::sortProductGUI);

	QObject::connect(undoButton, &QPushButton::clicked, this, &GUIModel::undoActionGUI);

	QObject::connect(addToCartButton, &QPushButton::clicked, this, &GUIModel::addToCartGUI);

	QObject::connect(tableView->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		auto selected = tableView->selectionModel()->selectedIndexes();
		if (selected.isEmpty()) {
			setId->setText("");
			setName->setText("");
			setType->setText("");
			setManufacturer->setText("");
			setPrice->setText("");
			return;
		}
		int selRow = selected.at(0).row();
		if (1) {
			auto cel0Index = tableView->model()->index(selRow, 0);
			auto cel1Index = tableView->model()->index(selRow, 1);
			auto cel2Index = tableView->model()->index(selRow, 2);
			auto cel3Index = tableView->model()->index(selRow, 3);
			auto cel4Index = tableView->model()->index(selRow, 4);

			auto cellValue1 = tableView->model()->data(cel0Index, Qt::DisplayRole).toString();
			auto cellValue2 = tableView->model()->data(cel1Index, Qt::DisplayRole).toString();
			auto cellValue3 = tableView->model()->data(cel2Index, Qt::DisplayRole).toString();
			auto cellValue4 = tableView->model()->data(cel3Index, Qt::DisplayRole).toString();
			auto cellValue5 = tableView->model()->data(cel4Index, Qt::DisplayRole).toString();
			setId->setText(cellValue1);
			setName->setText(cellValue2);
			setType->setText(cellValue3);
			setManufacturer->setText(cellValue4);
			setPrice->setText(cellValue5);
		}
		});

	QObject::connect(reloadButton, &QPushButton::clicked, [this]() { ReloadAllProducts(service.get_all_service()); });

	QObject::connect(cartButton, &QPushButton::clicked, [this]() {
		CartWindow* cart = new CartWindow{ service };
		cart->show();

		});
	QObject::connect(cartReadOnlyButton, &QPushButton::clicked, [this]() {
		CartGUIDraw* cart = new CartGUIDraw{ service };
		cart->show();
		});
}

void GUIModel::addProductGUI() {
	try {
		string id = setId->text().toStdString();
		string name = setName->text().toStdString();
		string type = setType->text().toStdString();
		string manufacturer = setManufacturer->text().toStdString();
		double price = setPrice->text().toDouble();

		setId->clear();
		setName->clear();
		setType->clear();
		setManufacturer->clear();
		setPrice->clear();

		if (service.genereaza_dictionar_pret_service()[price].empty()) {
			QPushButton* button = new QPushButton{ QString::number(price) };

			QObject::connect(button, &QPushButton::clicked, [this, price]() {
				QMessageBox::information(nullptr, "Numarul de entitati", QString::number(service.genereaza_dictionar_pret_service()[price].size()));
				});
		}

		this->service.adauga_service(id, name, type, manufacturer, price);
		ReloadAllProducts(service.get_all_service());
		QMessageBox::information(this, "Info", QString::fromStdString("Product added successfully!"));


	}
	catch (const RepoError& re) {
		QMessageBox::warning(this, "Add Warning", QString::fromStdString(string(re)));
	}
	catch (ValidationError& ve) {
		QMessageBox::warning(this, "Add Warning", QString::fromStdString(string(ve)));
	}
}

void GUIModel::deleteProductGUI() {
	try {
		string id = setId->text().toStdString();
		string name = setName->text().toStdString();
		string type = setType->text().toStdString();
		string manufacturer = setManufacturer->text().toStdString();
		double price = setPrice->text().toDouble();

		setId->clear();
		setName->clear();
		setType->clear();
		setManufacturer->clear();
		setPrice->clear();


		this->service.sterge_service(id);
		ReloadAllProducts(service.get_all_service());
		QMessageBox::information(this, "Info", QString::fromStdString("Product deleted successfully!"));

	}
	catch (const RepoError& re) {
		QMessageBox::warning(this, "Delete Warning", QString::fromStdString(string(re)));
	}
	catch (ValidationError& ve) {
		QMessageBox::warning(this, "Delete Warning", QString::fromStdString(string(ve)));
	}
}

void GUIModel::modifyProductGUI() {
	try {
		string id = setId->text().toStdString();
		string name = setName->text().toStdString();
		string type = setType->text().toStdString();
		string manufacturer = setManufacturer->text().toStdString();
		double price = setPrice->text().toDouble();

		setId->clear();
		setName->clear();
		setType->clear();
		setManufacturer->clear();
		setPrice->clear();

		this->service.modifica_service(id, name, type, manufacturer, price);
		ReloadAllProducts(service.get_all_service());
		QMessageBox::information(this, "Info", QString::fromStdString("Product modified successfully!"));

	}
	catch (const RepoError& re) {
		QMessageBox::warning(this, "Modify Warning", QString::fromStdString(string(re)));
	}
	catch (ValidationError& ve) {
		QMessageBox::warning(this, "Modify Warning", QString::fromStdString(string(ve)));
	}
}

void GUIModel::searchProductGUI() {
	try {
		string id = searchById->text().toStdString();
		searchById->clear();
		ReloadAllProducts(vector<Produs>{service.cauta_service(id)});
	}
	catch (const RepoError& re) {
		QMessageBox::warning(this, "Search Warning", QString::fromStdString(string(re)));
	}
	catch (ValidationError& ve) {
		QMessageBox::warning(this, "Search Warning", QString::fromStdString(string(ve)));
	}
}

void GUIModel::filterProductGUI() {
	if (priceFilterButton->isChecked()) {
		double price;
		if (price = setFilter->text().QString::toDouble()) {
			if (!service.filtreaza_pret_service(price).empty())
				ReloadAllProducts(service.filtreaza_pret_service(price));
			else
				QMessageBox::warning(this, "Filter Warning", "There are no products with the selected price!");
		}
		else
			QMessageBox::warning(this, "Filter Warning", "Price filter must be a real number different from 0!");
	}
	else if (nameFilterButton->isChecked()) {
		string name = setFilter->text().QString::toStdString();
		if (name != "") {
			if (!service.filtreaza_nume_service(name).empty())
				ReloadAllProducts(service.filtreaza_nume_service(name));
			else
				QMessageBox::warning(this, "Filter Warning", "There are no products with the selected name!");
		}
		else
			QMessageBox::warning(this, "Filter Warning", "Name cannot be empty!");
	}
	else if (manufacturerFilterButton->isChecked()) {
		string manufacturer = setFilter->text().QString::toStdString();
		if (manufacturer != "") {
			if (!service.filtreaza_producator_service(manufacturer).empty())
				ReloadAllProducts(service.filtreaza_producator_service(manufacturer));
			else
				QMessageBox::warning(this, "Filter Warning", "There are no products with the selected manufacturer!");
		}
		else
			QMessageBox::warning(this, "Filter Warning", "Manufacturer cannot be empty!");
	}
	else
		QMessageBox::warning(this, "Filter Warning", "You must select what you want to filter by!");
	setFilter->clear();
}

void GUIModel::sortProductGUI() {
	if (priceSortButton->isChecked())
		ReloadAllProducts(service.sort_pret());
	else if (nameSortButton->isChecked())
		ReloadAllProducts(service.sort_nume());
	else if (nameAndTypeSortButton->isChecked())
		ReloadAllProducts(service.sort_nume_tip());
	else
		QMessageBox::warning(this, "Sort Warning", "You must select what you want to sort by!");
}

void GUIModel::undoActionGUI() {
	try {
		service.undo_service();
		ReloadAllProducts(service.get_all_service());
	}
	catch (string error) {
		QMessageBox::warning(this, "Undo Warning", "Undo no longer available!");
	}
}

void GUIModel::addToCartGUI() {
	string name = setName->text().toStdString();

	setId->clear();
	setName->clear();
	setType->clear();
	setManufacturer->clear();
	setPrice->clear();

	service.adauga_cart_service(name);
}

void GUIModel::ReloadAllProducts(const vector<Produs>& all) {
	model->setProduse(all);
}