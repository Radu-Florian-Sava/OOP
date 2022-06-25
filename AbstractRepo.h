#pragma once
#include "Locatar.h"
#include <vector>
#include <map>

using std::vector;

class AbstractRepo
{
public:
	
	/*
	Salvare locatar
	arunca exceptie daca mai exista un locatar cu acelasi apartament
	*/
	virtual void adauga(const Locatar & l)=0;
	/*
	Modificare locatar
	arunca exceptie daca nu exista locatar la apartamentul referit
	*/
	virtual void modifica(const Locatar & l_nou)=0;
	/*
	Stergere locatar
	arunca exceptie daca nu exista locatar la apartamentul referit
	*/
	virtual void sterge(const Locatar & l)=0;
	/*
	Cauta
	arunca exceptie daca nu exista locatar
	*/
	virtual const Locatar& cauta(int apartament) const=0;

	/*
	returneaza toati locatarii
	*/
	virtual const vector<Locatar>& getAll() =0;

};

