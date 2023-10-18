#include "produs.h"

string Produs::get_id() const noexcept { return this->id; };

string Produs::get_nume() const { return this->nume; };

string Produs::get_tip() const { return this->tip; };

string Produs::get_producator() const { return this->producator; };

double Produs::get_pret() const noexcept { return this->pret; };

void Produs::set_nume(string _nume) { this->nume = _nume; };

void Produs::set_tip(string _tip) { this->tip = _tip; };

void Produs::set_producator(string _producator) { this->producator = _producator; };

void Produs::set_pret(double _pret) noexcept { this->pret = _pret; };

bool Produs::operator==(const Produs& p) const noexcept
{
	return p.get_id() == id;
}

ostream& operator<<(ostream& out, const Produs& p)
{
	out << p.get_id() << ' ' << p.get_nume() << ' ' << p.get_tip() << ' ' << p.get_producator() << ' ' << p.get_pret();
	return out;
}

ofstream& operator<<(ofstream& out, const Produs& p) {
	out << p.get_id() << ',' << p.get_nume() << ',' << p.get_tip() << ',' << p.get_producator() << ',' << p.get_pret();
	return out;
}

bool cmpNume(Produs p1, Produs p2) noexcept {
	return p1.get_nume() < p2.get_nume();
}

bool cmpPret(Produs p1, Produs p2) noexcept {
	return p1.get_pret() < p2.get_pret();
}

bool cmpNumeTip(Produs p1, Produs p2) noexcept {
	if (p1.get_nume() != p2.get_nume())
		return p1.get_nume() < p2.get_nume();
	return p1.get_tip() < p2.get_tip();
}