#pragma once
#include "repo_interface.h"

class Repository : public RepositoryInterface {
private:
	vector<Produs> produse;

public:
	//Default Repository constructor
	Repository() = default;
	//Deleted copy constructor
	Repository(const Repository& r) = delete;

	//Returns all the products in the store
	const vector<Produs>& get_all() const noexcept override;

	//Returns the number of products in the store
	long long size() const noexcept override;

	/// <summary>
	/// Adds a product to the store
	/// Throws RepoError if a product with the same id exists in the store
	/// </summary>
	void adauga_repo(const Produs&) override;

	/// <summary>
	/// Modifies a product from the store
	/// Throws RepoError if a product with the same id does not exist in the store
	/// </summary>
	/// <param name=""></param>
	void modifica_repo(const Produs&) override;

	/// <summary>
	/// Deletes a product from the store by id
	/// Throws RepoError if a product with the same id does not exist in the store
	/// </summary>
	/// <param name=""></param>
	void sterge_repo(const string&) override;

	/// <summary>
	/// Searches for a product from the store by id and returns it
	/// Throws RepoError if a product with the same id does not exist in the store
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	const Produs& cauta_repo(const string&) const override;
};