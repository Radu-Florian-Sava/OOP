#include "ExceptionRepo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void ExceptionRepo::adauga(const Locatar& l)
{
	double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (r < PROBABILITATE)
		throw RepoException("Probabilitate");
	if (exista(l)) {
		throw RepoException("Exista deja locatar la apartamentul:" + l.getApartament());
	}
	elems.emplace(l.getApartament(),l);
}

void ExceptionRepo::modifica(const Locatar& l_nou)
{
	double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (r < PROBABILITATE)
		throw RepoException("Probabilitate");
	if (!exista(l_nou)) {
		throw RepoException("Nu exista locatar la apartamentul:" + l_nou.getApartament());
	}
	else
	{
		for (auto& l : elems)
		{
			if (l.first == l_nou.getApartament())
			{
				l.second.setProprietar(l_nou.getProprietar());
				l.second.setSuprafata(l_nou.getSuprafata());
				l.second.setTip(l_nou.getTip());
				return;
			}
		}
	}
}

void ExceptionRepo::sterge(const Locatar& l) {
	double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (r < PROBABILITATE)
		throw RepoException("Probabilitate");
	if (elems.size() == 0) {
		throw RepoException("Nu exista locatar la apartamentul:" + l.getApartament());
	}
	if (!exista(l)) {
		throw RepoException("Nu exista locatar la apartamentul:" + l.getApartament());
	}
	else
	{
		for (map<int,Locatar>::iterator it = elems.begin(); it != elems.end(); ++it)
		{
			if (it->second.getApartament() == l.getApartament())
			{
				elems.erase(it);
				return;
			}
		}
	}
}

bool ExceptionRepo::exista(const Locatar& l) const {
	try {
		cauta(l.getApartament());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}
/*
Cauta
arunca exceptie daca nu exista locatar
*/
const Locatar& ExceptionRepo::cauta(int apartament) const {
	for (const auto& l : elems) {
		if (l.first == apartament) {
			return l.second;
		}
	}
	//daca nu exista arunc o exceptie
	throw RepoException("Nu exista locatar la apartamentul:" + apartament);
}

void ExceptionRepo::mapToVector() {
	substitutie.clear();
	for (auto l : elems) {
		substitutie.push_back(l.second);
	}
	return;
}

/*
returneaza toati locatarii salvati
*/
const vector<Locatar>& ExceptionRepo::getAll()  {
	double r = static_cast <double> (rand()) / static_cast <double> (RAND_MAX);
	if (r < PROBABILITATE)
		throw RepoException("Probabilitate");
	mapToVector();
	return substitutie;
}



