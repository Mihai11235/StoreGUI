#include "file_repository.h"

void FileRepository::write_all_to_file() {
	ofstream fout(file);
	//if (!fout.is_open())
	//	throw RepoError("Error while opening file " + file + " for writing!\n");

	for (const Produs& p : get_all()) {
		fout << p << '\n';
	}
	fout.close();
}

void FileRepository::read_all_from_file() {
	ifstream fin(file);
	if (!fin.is_open())
		throw RepoError("Error while opening file " + file + " for reading!\n");

	string id; string name, type, manufacturer; double price;

	while (!fin.eof() && !std::filesystem::is_empty(file)) { //From c++17 : is_empty("file_name")

		string s;
		getline(fin, s);
		if (s == "")
			break;
		istringstream iss(s);

		string ok;
		getline(iss, id, ','); 
		getline(iss, name, ',');
		getline(iss, type, ',');
		getline(iss, manufacturer, ',');
		getline(iss, ok, ','); price = std::stod(ok);
		Produs p{ id, name, type, manufacturer, price };
		Repository::adauga_repo(p);
	}
	fin.close();
}

void FileRepository::adauga_repo(const Produs& p) {
	Repository::adauga_repo(p);
	write_all_to_file();
}

void FileRepository::modifica_repo(const Produs& p) {
	Repository::modifica_repo(p);
	write_all_to_file();
}

void FileRepository::sterge_repo(const string& id) {
	Repository::sterge_repo(id);
	write_all_to_file();
}