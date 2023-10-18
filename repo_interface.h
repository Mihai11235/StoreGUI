#pragma once
#pragma warning (disable: 26823)
#include "produs.h"
#include <vector>
#include <algorithm>


using std::vector;
using std::copy_if;

//Class for throwing errors
class RepoError {
private:
	string errors;

public:
	//RepoError constructor
	RepoError(const string& _errors) :errors{ _errors } {};
	//Overloaded string() operator for convertion from RepoError to string
	operator string() const;
};

class RepositoryInterface {
private:
	vector<Produs> produse;

public:

	//Returns all the products in the store
	virtual const vector<Produs>& get_all() const noexcept = 0;

	//Returns the number of products in the store
	virtual long long size() const noexcept = 0;

	/// <summary>
	/// Adds a product to the store
	/// Throws RepoError if a product with the same id exists in the store
	/// </summary>
	virtual void adauga_repo(const Produs&) = 0;

	/// <summary>
	/// Modifies a product from the store
	/// Throws RepoError if a product with the same id does not exist in the store
	/// </summary>
	/// <param name=""></param>
	virtual void modifica_repo(const Produs&) = 0;

	/// <summary>
	/// Deletes a product from the store by id
	/// Throws RepoError if a product with the same id does not exist in the store
	/// </summary>
	/// <param name=""></param>
	virtual void sterge_repo(const string&) = 0;

	/// <summary>
	/// Searches for a product from the store by id and returns it
	/// Throws RepoError if a product with the same id does not exist in the store
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	virtual const Produs& cauta_repo(const string&) const = 0;
};