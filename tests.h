#pragma once
#include "produs.h"
#include "validator.h"
#include "repository.h"
#include "service.h"
#include <cassert>
#include <fstream>
#include "file_repository.h"

using std::getline;

class Tests {
private:
	void run_domain_tests();
	void run_validator_tests();
	void run_repo_rests();
	void run_service_tests();
	void run_file_repo_tests();
	void run_undo_tests();
	Validator val;
	Repository repo;
	Cart cart;
	Service service{ repo, val, cart };
	FileRepository file_repo{ "Tests.txt" };

public:
	void run_all_tests();
};