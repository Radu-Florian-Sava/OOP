#include "Repo.h"
#include <assert.h>
#include <iostream>
#include <sstream>

using std::ostream;
using std::stringstream;

void Repo::adauga(const Locatar& l) 
 {
	if (exista(l)) {
		throw RepoException("Exista deja locatar la apartamentul:" + l.getApartament());
	}
	elems.push_back(l);
}

void Repo::modifica(const Locatar& l_nou) 
{
	if (!exista(l_nou)) {
		throw RepoException("Nu exista locatar la apartamentul:" + l_nou.getApartament());}
	else
	{
		for (auto& l : elems)
		{
			if (l.getApartament() == l_nou.getApartament())
			{
				l.setProprietar(l_nou.getProprietar());
				l.setSuprafata(l_nou.getSuprafata());
				l.setTip(l_nou.getTip());
				return;
			}
		}
	}
}

void Repo::sterge(const Locatar& l) {
	if (elems.size() == 0) {
		throw RepoException("Nu exista locatar la apartamentul:" + l.getApartament());
	}
	if (!exista(l)) {
		throw RepoException("Nu exista locatar la apartamentul:" + l.getApartament());}
	else
	{
		for (vector<Locatar>::iterator it = elems.begin(); it !=elems.end(); ++it)
		{
			if (it->getApartament() == l.getApartament())
			{	
				elems.erase(it);
				return;
			}
		}
	}
}

bool Repo::exista(const Locatar& l) const {
	try {
		cauta(l.getApartament());
		return true;
	}
	catch (RepoException&) {
		return false;}
}
/*
Cauta
arunca exceptie daca nu exista locatar
*/
const Locatar& Repo::cauta(int apartament) const {
	for (const auto& l : elems) {
		if (l.getApartament() == apartament) {
			return l;
		}
	}
	//daca nu exista arunc o exceptie
	throw RepoException("Nu exista locatar la apartamentul:" + apartament);}

/*
returneaza toati locatarii salvati
*/
const vector<Locatar>& Repo::getAll()  noexcept {
	return elems;
}


ostream& operator<<(ostream& out, const RepoException& ex) {
	out << ex.msg;
	return out;
}




void testAdauga() {
	Repo rep;
	rep.adauga(Locatar{ 1,"a",4,"a" });
	assert(rep.getAll().size() == 1);
	assert(rep.cauta(1).getApartament() == 1);

	rep.adauga(Locatar{ 2,"b",4 ,"b"});
	assert(rep.getAll().size() == 2);

	//nu pot adauga 2 cu acelasi apartament
	try {
		rep.adauga(Locatar{ 1,"a",4,"a" });
		assert(false);}
	catch (const RepoException&) {
		assert(true);
	}
	//cauta inexistent
	try {
		rep.cauta(3);
		assert(false);}
	catch (const RepoException& e) {
		stringstream os;
		os << e;
		assert(os.str().find("exista") >= 0);
	}
}

void testCauta() {
	Repo rep;
	rep.adauga(Locatar { 1, "a", 4 ,"a"});
	rep.adauga(Locatar{ 2,"b", 4 ,"b"});

	auto p{ rep.cauta(1) };
	assert(p.getApartament() == 1);

	//arunca exceptie daca nu gaseste
	try {
		rep.cauta(3);
		assert(false);}
	catch (RepoException&) {
		assert(true);
	}
}

void testSterge() {
	Repo rep;
	rep.adauga(Locatar{ 1,"a",4,"a" });
	rep.adauga(Locatar{ 2,"b",4 ,"b" });
	
	rep.sterge(Locatar{ 1,"b",5,"c" });
	assert(rep.getAll().size() == 1);
	try {
		rep.sterge(Locatar{ 3,"c",2,"c" });
		assert(false);}
	catch (const RepoException&) {
		assert(true);
	}
		rep.sterge(Locatar{2,"b",10,"d"});
	assert(rep.getAll().size() == 0);
	try {
		rep.sterge(Locatar{ 2,"b",10,"d" });
		assert(false);}
	catch (const RepoException&) {
		assert(true);
	}
	try {
		rep.sterge(Locatar{ -1,"b",10,"d" });
		assert(false);}
	catch (const RepoException&) {
		assert(true);
	}
}

void testModifica() {
	Repo rep;
	rep.adauga(Locatar{ 1, "a", 4 ,"a" });
	rep.adauga(Locatar{ 2,"b", 4 ,"b" });
	rep.modifica(Locatar{ 1,"c",6,"c" });
	assert(rep.getAll().at(0).getSuprafata() == 6);
	//arunca exceptie daca nu gaseste
	try {
		rep.modifica(Locatar{ 4,"d",4,"d" });
		assert(false);}
	catch (RepoException&) {
		assert(true);
	}
}

void testeRepo() {
	testAdauga();
	testCauta();
	testModifica();
	testSterge();
}