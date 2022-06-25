#pragma once
#include <string>
#include "Locatar.h"
#include <vector>

// folosim namespace-ul corespunzator string, vector si ostream

using std::vector;
using std::string;
using std::ostream;

class ValidateException {
	// clasa care ridica eraore la validare daca este cazul

	vector<string> msgs;
public:
	ValidateException(const vector<string>& errors) :msgs{ errors } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const ValidateException& ex);
};

ostream& operator<<(ostream& out, const ValidateException& ex);

class LocatarValidator {
	// clasa propriu-zisa de validator pentru elementele din domeniul aplicatiei
public:
	/*
	metoda care valideaza obiectul de tip Locatar transmis ca parametru
	*/
	void valideaza(const Locatar& l);
};
/*
metoda care ruleaza testele validatorului
*/
void testValidator();

