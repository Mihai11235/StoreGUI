#pragma once
#include "produs.h"
#include <vector>
#include <chrono>
#include <random>
#include<algorithm>

using std::vector;

//Class for throwing errors
class CartError {
private:
	string errors;
public:
	CartError(const string& _errors) : errors{ _errors } {};
	operator string();
};


class Cart {
private:
	vector<Produs> cos;
	double pret_total;

public:
	//Default constructor
	Cart() = default;

	//Deleted copy constructor
	Cart(const Cart&) = delete;

	//Adds products to cart by name
	void adauga_cart(const Produs& p);

	//Empties the cart
	void goleste_cart();

	//returns the total price of the products in the cart
	double get_pret_total_cart();

	/// <summary>
	/// Randomly generates products from the store in the cart
	/// Throws CartError if there are not enough 
	/// </summary>
	void genereaza_cart(vector<Produs> elems, int nrElems);

	//Exports the products from the cart to a file
	void export_cart(string file);

	vector<Produs> get_all();
};
