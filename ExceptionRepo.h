#pragma once
#include "Locatar.h"
#include "Repo.h"
#include "AbstractRepo.h"
#include <map>
#include <vector>

using std::map;
using std::vector;

class ExceptionRepo: public AbstractRepo{
	map<int,Locatar> elems;
	vector<Locatar> substitutie;
	/*
	metoda privata verifica daca exista deja l in repository
	*/
	bool exista(const Locatar& l) const;

	double PROBABILITATE;
public:
	ExceptionRepo(const double PROBABILITATE) :PROBABILITATE{PROBABILITATE} {

	}
	
	ExceptionRepo(const Repo & ot) = delete;
	/*
	Salvare locatar
	arunca exceptie daca mai exista un locatar cu acelasi apartament
	*/
	void adauga(const Locatar & l) override;
	/*
	Modificare locatar
	arunca exceptie daca nu exista locatar la apartamentul referit
	*/
	void modifica(const Locatar & l_nou) override;
	/*
	Stergere locatar
	arunca exceptie daca nu exista locatar la apartamentul referit
	*/
	void sterge(const Locatar & l) override;
	/*
	Cauta
	arunca exceptie daca nu exista locatar
	*/
	const Locatar& cauta(int apartament) const override;


	void mapToVector();
	/*
	returneaza toati locatarii
	*/
	const vector<Locatar>& getAll()  override;

};

