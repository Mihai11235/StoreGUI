#include "shopping_cart.h"

CartError::operator string() {
	return errors;
}

void Cart::adauga_cart(const Produs& p)
{
	cos.push_back(p);
	pret_total += p.get_pret();
}

void Cart::goleste_cart()
{
	cos.clear();
	pret_total = 0;
}

double Cart::get_pret_total_cart()
{
	return pret_total;
}

void Cart::genereaza_cart(vector<Produs> elems, int nrElems)
{
	int copy = nrElems;
	while (copy) {
		auto seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(elems.begin(), elems.end(), std::default_random_engine(unsigned(seed)));
		cos.push_back(elems.back());
		pret_total += elems.back().get_pret();
		copy--;
	}
}

void Cart::export_cart(string file) {
	ofstream fout(file);
	if (!fout.is_open())
		throw CartError("Error while opening file " + file + " for writing!\n");

	for (const Produs& p : cos) {
		fout << p << '\n';
	}
	fout.close();
}

vector<Produs> Cart::get_all() {
	return cos;
}
