#pragma once
#include "Locatar.h"

#include <vector>
#include <string>
#include <ostream>
#include "AbstractRepo.h"

// folosim namespace-ul corespunzator string, vector si ostream

using std::vector;
using std::string;
using std::ostream;

class Repo : public AbstractRepo{
	vector<Locatar> elems;
	/*
	metoda privata verifica daca exista deja l in repository
	*/
	bool exista(const Locatar& l) const;
public:
	Repo() = default;
	//nu permitem copierea de obiecte
	Repo(const Repo& ot) = delete;
	/*
	Salvare locatar
	arunca exceptie daca mai exista un locatar cu acelasi apartament
	*/
	void adauga(const Locatar& l) override;
	/*
	Modificare locatar
	arunca exceptie daca nu exista locatar la apartamentul referit
	*/
	void modifica(const Locatar& l_nou) override;
	/*
	Stergere locatar
	arunca exceptie daca nu exista locatar la apartamentul referit
	*/
	void sterge(const Locatar& l) override;
	/*
	Cauta
	arunca exceptie daca nu exista locatar
	*/
	const Locatar& cauta(int apartament) const override;

	/*
	returneaza toati locatarii
	*/
	const vector<Locatar>& getAll()  noexcept override;

};

/*
Folosit pentru a semnala situatii exceptionale care pot aparea in repo
*/
class RepoException {
	string msg;
public:
	RepoException(string m) :msg{ m } {}
	//functie friend (vreau sa folosesc membru privat msg)
	friend ostream& operator<<(ostream& out, const RepoException& ex);
};

ostream& operator<<(ostream& out, const RepoException& ex);

/*
metoda care ruleaza testele pentru repository
*/
void testeRepo();