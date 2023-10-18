#pragma once
#include "repository.h"
#include "validator.h"
#include <functional>
#include "shopping_cart.h"
#include <unordered_map>
#include <memory>
#include "undo_action.h"
#include "observer.h"

using std::unordered_map;
using std::function;
using std::unique_ptr;


class Service : public Observable {
private:
	// Dependence injection of Repository, Validator and Cart objects
	RepositoryInterface& repo;
	const Validator& val;
	Cart& cart;
	vector<unique_ptr<UndoAction>> UndoActions;

public:
	//Deleted default constructor
	Service() = delete;
	//Service constructor
	Service(RepositoryInterface& _repo, const Validator& _val, Cart& _cart) noexcept :repo{ _repo }, val{ _val }, cart{ _cart } {};
	//Deleted copy constructor
	Service(const Service& service) = delete;

	//Returns all the products in the store
	const vector<Produs>& get_all_service() const noexcept;

	//Adds a product to the store
	void adauga_service(const string&, const string&, const string&, const string&, const double&);

	//Modifies a product from the store
	void modifica_service(const string&, const string&, const string&, const string&, const double&);

	//Deletes a product from the store by id
	void sterge_service(const string&);

	//Searches a product from the store by id and returns it
	const Produs& cauta_service(const string&) const;

	//Filters products, is called by filtreaza_pret_service, filtreaza_nume_service, filtreaza_producator_service
	const vector<Produs> filtreaza_service(function<bool(const Produs&)>);

	//Filters products by price and returns them
	const vector<Produs> filtreaza_pret_service(double pret);

	//Filters products by name and returns them
	const vector<Produs> filtreaza_nume_service(string nume);

	//Filters products by manufacturer and returns them
	const vector<Produs> filtreaza_producator_service(string producator);

	//Sorts products by name and returns them
	const vector<Produs> sort_nume();

	//Sorts products by price and returns them
	const vector<Produs> sort_pret();

	//Sorts products, first by name and then by type and returns them
	const vector<Produs> sort_nume_tip();

	//Adds products to cart by name
	void adauga_cart_service(string nume);

	//Empties the cart
	void goleste_cart_service();

	//returns the total price of the products in the cart
	double get_pret_total_cart_service();

	vector<Produs> get_all_cart_service();

	//Randomly generates products from the store in the cart
	void genereaza_cart_service(int nrElems);

	//Unordered Map of products mapped by price
	unordered_map<double, vector<Produs>> genereaza_dictionar_pret_service();

	//Exports the products from the cart to a file
	void export_cart_service(string);

	//Undo the last operation
	void undo_service();
};