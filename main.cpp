#include "tests.h"
#include <assert.h>
#include "shopping_cart.h"
#include "file_repository.h"
#include "gui.h"
#include <QApplication>
#include <QStyleFactory>
#include "GUI.h"

void run_tests() {
	Tests tests;
	tests.run_all_tests();
}

int main(int argc, char** argv) {
	run_tests();
	QApplication app(argc, argv);
	qApp->setStyle(QStyleFactory::create("Fusion"));
	
	Validator val;
	Repository MemoryRepo;
	FileRepository FileRepo{ "products.txt" };
	Cart cart;
	Service service{ FileRepo, val, cart };

	GUIModel* console = new GUIModel{ service };
	console->show();


	return app.exec();
}