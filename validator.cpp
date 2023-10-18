#include "validator.h"

ValidationError::operator string() {
	return errors;
}

void Validator::valideaza(const Produs& p) const {
	string errors = "";

	if (p.get_id() == "" || p.get_id()[0] == '-')
		errors += "Id invalid!\n";

	if (p.get_nume() == "")
		errors += "Nume invalid!\n";

	if (p.get_tip() == "")
		errors += "Tip invalid!\n";

	if (p.get_producator() == "")
		errors += "Producator invalid!\n";

	if (p.get_pret() < 0)
		errors += "Pret invalid!\n";

	if (errors.size())
		throw ValidationError(errors);
}
