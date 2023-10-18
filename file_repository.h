#pragma once
#include "repository.h"
#include <filesystem>

using std::istringstream;
using std::ifstream;
using std::getline;

class FileRepository : public Repository {
private:
	string file;

	//Reads all products from CSV file
	void read_all_from_file();

	//Writes all products to CSV file
	void write_all_to_file();

public:
	//FileRepository constructor
	FileRepository(const string& file) : file{ file } { read_all_from_file(); };

	//Overriden adauga_repo method, it calls the Base Class method and updates the file
	void adauga_repo(const Produs&) override;

	//Overriden modifica_repo method, it calls the Base Class method and updates the file
	void modifica_repo(const Produs&) override;

	//Overriden sterge_repo method, it calls the Base Class method and updates the file
	void sterge_repo(const string&) override;
};