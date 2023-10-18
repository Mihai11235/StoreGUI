#pragma once
#include "produs.h"

//Class for throwing errors
class ValidationError {
private:
	string errors;
public:
	ValidationError(const string& _errors) : errors{ _errors } {};
	operator string();
};

class Validator {
public:
	/// <summary>
	/// Validates the product
	/// Throws ValidationError if the product is not valid
	/// </summary>
	void valideaza(const Produs&) const;
};