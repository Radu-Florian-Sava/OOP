#include "Validator.h"
#include <assert.h>
#include <sstream>

void LocatarValidator::valideaza(const Locatar& l) {
	vector<string> msgs;
	if (l.getSuprafata() < 0) msgs.push_back("Suprafata negativa!!!");
	if (l.getTip().size() == 0) msgs.push_back("Tip vid!!!");
	if (l.getProprietar().size() == 0) msgs.push_back("Proprietar vid!!!");
	if (l.getApartament() <= 0) msgs.push_back("Apartament negaitv!!!");
	if (msgs.size() > 0) {
		throw ValidateException(msgs);
	}
}

ostream& operator<<(ostream& out, const ValidateException& ex) {
	for (const auto& msg : ex.msgs) {
		out << msg << " ";
	}
	return out;
}

void testValidator() {
	LocatarValidator v;
	Locatar l{ -1, "", -1, "" };
	try {
		v.valideaza(l);}
	catch (const ValidateException& ex) {
		std::stringstream sout;
		sout << ex;
		const auto mesaj = sout.str();
		assert(mesaj.find("negativ") >= 0);
		assert(mesaj.find("vid") >= 0);
	}

}
