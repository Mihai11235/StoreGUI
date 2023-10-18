#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
using std::cout;

using std::string;
using std::ostream;
using std::ofstream;

class Produs {
private:
	string id;
	string nume;
	string tip;
	string producator;
	double pret;

public:
	//Deleted default constructor
	Produs() = delete;
	//Produs constructor
	Produs(const string& id, const string& nume, const string& tip, const string& producator, const double& pret) :id{ id }, nume{ nume }, tip{ tip }, producator{ producator }, pret{ pret } {};

	/*Produs(const Produs& p) :id{ p.get_id() }, nume{ p.get_nume() }, tip{ p.get_tip() }, producator{ p.get_producator() }, pret{ p.get_pret()} {
		cout << "Copy constructor called!\n";
	}*/
	//Produs(const Produs& p) = delete;

	//Returns the id of the product
	string get_id() const noexcept;
	//Returns the name of the product
	string get_nume() const;
	//Returns the type of the product
	string get_tip() const;
	//Returns the manufacturer of the product
	string get_producator() const;
	//Returns the price of the product
	double get_pret() const noexcept;

	//Sets the name of the product
	void set_nume(string);
	//Sets the type of the product
	void set_tip(string);
	//Sets the manufacturer of the product
	void set_producator(string);
	//Sets the price of the product
	void set_pret(double) noexcept;

	//Overloads the == operator to be able to compare 2 products
	bool operator==(const Produs& p)const noexcept;
};

//Overloads the << operator to be able to print a product
ostream& operator<<(ostream& out, const Produs& p);

//Overloads the << operator to be able to print a product to file
ofstream& operator<<(ofstream& out, const Produs& p);

//Returns true if the name of the first product is "smaller" than the name of the second, false otherwise
bool cmpNume(Produs p1, Produs p2) noexcept;

//Returns true if the price of the first product is "smaller" than the price of the second, false otherwise
bool cmpPret(Produs p1, Produs p2) noexcept;

//Returns true if the name of the first product is "smaller" than the name of the 
// second, or if the names are the same and the type of the first is "smaller"
// than the type of the second, false otherwise
bool cmpNumeTip(Produs p1, Produs p2) noexcept;