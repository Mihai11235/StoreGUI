#include "service.h"

const vector<Produs>& Service::get_all_service() const noexcept {
	return repo.get_all();
}

void Service::adauga_service(const string& id, const string& nume, const string& tip, const string& producator, const double& pret) {
	Produs p(id, nume, tip, producator, pret);
	val.valideaza(p);

	UndoActions.push_back(unique_ptr<UndoAction>{new UndoAdd{ p, repo }});
	repo.adauga_repo(p);
}

void Service::modifica_service(const string& id, const string& nume, const string& tip, const string& producator, const double& pret) {
	Produs p(id, nume, tip, producator, pret);
	val.valideaza(p);

	UndoActions.push_back(unique_ptr<UndoAction>{new UndoModify{ cauta_service(p.get_id()), repo }});
	repo.modifica_repo(p);
}

void Service::sterge_service(const string& id) {
	UndoActions.push_back(unique_ptr<UndoAction>{new UndoRemove{ repo.cauta_repo(id), repo }});
	repo.sterge_repo(id);
}

const Produs& Service::cauta_service(const string& id) const {
	return repo.cauta_repo(id);
}

const vector<Produs> Service::filtreaza_service(function<bool(const Produs&)> f) {
	vector<Produs> filtered;
	copy_if(repo.get_all().begin(), repo.get_all().end(), std::back_inserter(filtered), f);
	return filtered;
}

const vector<Produs> Service::filtreaza_pret_service(double pret) {
	return filtreaza_service([&pret](const Produs& p) noexcept {return p.get_pret() == pret; });
}

const vector<Produs> Service::filtreaza_nume_service(string nume) {
	return filtreaza_service([&nume](const Produs& p) {return p.get_nume() == nume; });
}

const vector<Produs> Service::filtreaza_producator_service(string producator) {
	return filtreaza_service([&producator](const Produs& p) {return p.get_producator() == producator; });
}

const vector<Produs> Service::sort_nume()
{
	vector<Produs> copy = repo.get_all();
	sort(copy.begin(), copy.end(), cmpNume);
	return copy;
}

const vector<Produs> Service::sort_pret()
{
	vector<Produs> copy = repo.get_all();
	sort(copy.begin(), copy.end(), cmpPret);
	return copy;
}

const vector<Produs> Service::sort_nume_tip()
{
	vector<Produs> copy = repo.get_all();
	sort(copy.begin(), copy.end(), cmpNumeTip);
	return copy;
}

void Service::adauga_cart_service(string nume)
{
	vector<Produs> produse = repo.get_all();
	for (const Produs& p : produse)
		if (p.get_nume() == nume)
			cart.adauga_cart(p);
}

void Service::goleste_cart_service()
{
	cart.goleste_cart();
	notify();
}

double Service::get_pret_total_cart_service()
{
	return cart.get_pret_total_cart();
}

vector<Produs> Service::get_all_cart_service() {
	return cart.get_all();
}

void Service::genereaza_cart_service(int nrElems)
{
	cart.genereaza_cart(repo.get_all(), nrElems);
	notify();
}

unordered_map<double, vector<Produs>> Service::genereaza_dictionar_pret_service()
{
	unordered_map<double, vector<Produs>> map;
	for (const Produs& p : repo.get_all()) {
		map[p.get_pret()].push_back(p);
	}
	return map;

}

void Service::export_cart_service(string file) {
	cart.export_cart(file);
}

void Service::undo_service() {
	if (UndoActions.empty())
		throw string("Nu se mai poate face undo!");

	UndoActions.back()->doUndo();
	UndoActions.pop_back();
}

