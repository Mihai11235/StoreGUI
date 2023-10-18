#include "tests.h"

void Tests::run_all_tests() {
	run_undo_tests();
	run_domain_tests();
	run_validator_tests();
	run_repo_rests();
	run_service_tests();
	run_file_repo_tests();
}

void Tests::run_domain_tests() {
	Produs p1("1", "twix", "alimentar", "eu", 3);

	assert(p1.get_id() == "1");
	assert(p1.get_nume() == "twix");
	assert(p1.get_tip() == "alimentar");
	assert(p1.get_producator() == "eu");
	assert(p1.get_pret() == 3);

	p1.set_nume("snickers");
	p1.set_tip("alt tip");
	p1.set_producator("alt producator");
	p1.set_pret(4);

	assert(p1.get_nume() == "snickers");
	assert(p1.get_tip() == "alt tip");
	assert(p1.get_producator() == "alt producator");
	assert(p1.get_pret() == 4);

	std::ostringstream os;
	os << p1;
	assert(os.str() == "1 snickers alt tip alt producator 4");
}

void Tests::run_validator_tests() {
	Produs p1("1", "twix", "alimentar", "eu", 3);
	val.valideaza(p1);

	Produs p2("-1", "", "", "", -1);
	try {
		val.valideaza(p2);
	}
	catch (ValidationError ve) {
		assert(string(ve) == "Id invalid!\nNume invalid!\nTip invalid!\nProducator invalid!\nPret invalid!\n");
	}

}

void Tests::run_repo_rests() {
	//adauga
	Produs p1("1", "twix", "alimentar", "eu", 3);
	Produs p2("1", "twixx", "nealimentar", "nu eu", 6);
	Produs p3("2", "snickers", "alimentar", "eu", 6);
	Produs p4("10", "snickers", "alimentar", "eu", 6);

	repo.adauga_repo(p1);
	repo.adauga_repo(p3);
	repo.adauga_repo(p4);
	repo.sterge_repo("2");
	repo.sterge_repo("10");

	assert(repo.get_all().front().get_id() == "1");
	assert(repo.size() == 1);

	try {
		repo.adauga_repo(p2);
	}
	catch (RepoError re) {
		assert(string(re) == "Produs existent!");
	}
	assert(repo.size() == 1);

	//modifica
	repo.modifica_repo(p2);
	assert(repo.get_all().front().get_id() == "1");

	try {
		repo.modifica_repo(p3);
	}
	catch (RepoError re) {
		assert(string(re) == "Produs inexistent!");
	}
	assert(repo.size() == 1);

	//sterge
	try {
		repo.sterge_repo("2");
	}
	catch (RepoError re) {
		assert(string(re) == "Produs inexistent!");
	}
	assert(repo.size() == 1);

	repo.sterge_repo("1");
	assert(repo.size() == 0);

	//cauta
	try {
		repo.cauta_repo("9");
	}
	catch (RepoError re) {
		assert(string(re) == "Produs inexistent!");
	}

	repo.adauga_repo(p4);
	assert(p4 == repo.cauta_repo("10"));
	repo.sterge_repo("10");
}

void Tests::run_file_repo_tests() {
	//adauga, sterge

	Produs p1("1", "twix", "alimentar", "eu", 3);
	Produs p2("1", "twixx", "nealimentar", "nu eu", 6);
	Produs p3("2", "snickers", "alimentar", "eu", 6);
	Produs p4("10", "snickers", "alimentar", "eu", 6);


	file_repo.adauga_repo(p1);
	file_repo.adauga_repo(p3);
	file_repo.sterge_repo("2");


	ifstream fin("Tests.txt");
	string line;
	getline(fin, line);
	assert(line == "10,snickers,alimentar,eu,6");
	getline(fin, line);
	assert(line == "1,twix,alimentar,eu,3");
	fin.close();

	//modifica
	file_repo.modifica_repo(p2);
	fin.open("Tests.txt");
	getline(fin, line);
	assert(line == "10,snickers,alimentar,eu,6");
	getline(fin, line);
	assert(line == "1,twixx,nealimentar,nu eu,6");
	fin.close();

	file_repo.sterge_repo("1");
	file_repo.sterge_repo("10");

	ofstream fout("Tests.txt");
	fout.close();
	file_repo.adauga_repo(p4);


	try {
		FileRepository fr{ "" };
	}
	catch (RepoError re) {
		assert(string(re) == "Error while opening file  for reading!\n");
	}
}

void Tests::run_undo_tests() {
	service.adauga_service("8", "a", "a", "a", 10);
	service.modifica_service("8", "b", "b", "b", 1);
	service.sterge_service("8");
	assert(repo.size() == 0);

	service.undo_service();
	assert(repo.size() == 1);
	assert(service.cauta_service("8").get_nume() == "b");
	service.undo_service();
	assert(repo.size() == 1);
	assert(service.cauta_service("8").get_nume() == "a");
	service.undo_service();
	assert(repo.size() == 0);

	try {
		service.undo_service();
	}
	catch (const string& s) {
		assert(s == "Nu se mai poate face undo!");
	}
}

void Tests::run_service_tests() {
	//adauga
	service.adauga_service("3", "twix", "alimentar", "eu", 3);
	assert(service.get_all_service().front().get_id() == "3");

	try {
		service.adauga_service("3", "twixx", "nealimentar", "nu eu", 6);
	}
	catch (RepoError re) {
		assert(string(re) == "Produs existent!");
	}

	//modifica
	service.modifica_service("3", "twixx", "nealimentar", "nu eu", 6);
	try {
		service.modifica_service("4", "snickers", "alimentar", "eu", 6);
	}
	catch (RepoError re) {
		assert(string(re) == "Produs inexistent!");
	}

	//sterge
	try {
		service.sterge_service("2");
	}
	catch (RepoError re) {
		assert(string(re) == "Produs inexistent!");
	}

	service.sterge_service("3");
	assert(service.get_all_service().size() == 0);

	//cauta
	try {
		service.cauta_service("9");
	}
	catch (RepoError re) {
		assert(string(re) == "Produs inexistent!");
	}

	service.adauga_service("10", "snickers", "alimentar", "eu", 6);
	assert(repo.cauta_repo("10").get_id() == "10");
	service.sterge_service("10");

	//filtreaza
	Produs p1("3", "a", "a", "eu", 5);
	Produs p2("4", "a", "g", "eu", 3);
	Produs p3("5", "a", "c", "eu", 2);
	Produs p4("6", "e", "a", "eu", 3);
	Produs p5("7", "d", "a", "eu", 10);

	repo.adauga_repo(p1);
	repo.adauga_repo(p2);
	repo.adauga_repo(p3);
	repo.adauga_repo(p4);
	repo.adauga_repo(p5);

	vector<Produs> filtrat = service.filtreaza_nume_service("a");
	assert(filtrat.size() == 3);

	filtrat = service.filtreaza_pret_service(3);
	assert(filtrat.size() == 2);

	filtrat = service.filtreaza_producator_service("eu");
	assert(filtrat.size() == 5);

	vector<Produs> sortat = service.sort_nume();
	assert(sortat[0] == p1);
	assert(sortat[1] == p2);
	assert(sortat[2] == p3);
	assert(sortat[3] == p5);
	assert(sortat[4] == p4);

	sortat = service.sort_pret();
	assert(sortat[0] == p3);
	assert(sortat[1] == p2);
	assert(sortat[2] == p4);
	assert(sortat[3] == p1);
	assert(sortat[4] == p5);

	sortat = service.sort_nume_tip();
	assert(sortat[0] == p1);
	assert(sortat[1] == p3);
	assert(sortat[2] == p2);
	assert(sortat[3] == p5);
	assert(sortat[4] == p4);

	//adauga cos
	service.adauga_cart_service("a");
	assert(service.get_pret_total_cart_service() == 10);

	//goleste cos
	service.goleste_cart_service();
	assert(service.get_pret_total_cart_service() == 0);

	//genereaza cos
	service.genereaza_cart_service(5);
	assert(cart.get_pret_total_cart() > 0);

	//export
	try {
		service.export_cart_service("");
	}
	catch (CartError ce) {
		assert(string(ce) == "Error while opening file  for writing!\n");
	}

	service.export_cart_service("Teste_cart.txt");

	ifstream fin("Teste_cart.txt");

	string s;
	int nr = 0;
	while (getline(fin, s))
		nr++;
	assert(nr == 5);

	unordered_map<double, vector<Produs>> map = service.genereaza_dictionar_pret_service();
	assert(map.at(3).size() == 2);
}
