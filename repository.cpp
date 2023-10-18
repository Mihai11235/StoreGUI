#include "repository.h"

RepoError::operator string() const {
	return errors;
}

const vector<Produs>& Repository::get_all() const noexcept {
	return produse;
}

void Repository::adauga_repo(const Produs& p) {

	vector<Produs>::const_iterator it = find_if(produse.begin(), produse.end(), [&p](const Produs& _p) {return _p == p; });

	if (it != produse.end())
		throw RepoError("Produs existent!");

	produse.push_back(p);
}

long long Repository::size() const noexcept {
	return produse.size();
}

void Repository::modifica_repo(const Produs& p) {

	vector<Produs>::iterator it = find_if(produse.begin(), produse.end(), [&p](const Produs& _p) {return _p == p; });

	if (it == produse.end())
		throw RepoError("Produs inexistent!");


	it->set_nume(p.get_nume());
	it->set_tip(p.get_tip());
	it->set_producator(p.get_producator());
	it->set_pret(p.get_pret());

}


void Repository::sterge_repo(const string& id) {
	vector<Produs>::const_iterator it = find_if(produse.begin(), produse.end(), [&id](const Produs& p) {return p.get_id() == id; });

	if (it == produse.end())
		throw RepoError("Produs inexistent!");

	produse.erase(it);

}

const Produs& Repository::cauta_repo(const string& id) const {
	vector<Produs>::const_iterator i = find_if(produse.begin(), produse.end(), [&id](const Produs& p) {return p.get_id() == id; });
	if (i != produse.end())
		return *i;
	throw RepoError("Produs inexistent!");
}
