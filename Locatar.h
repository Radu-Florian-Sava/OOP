#pragma once
#include <string>
#include <iostream>

// folosim namespace-ul corespunzator string si cout
using std::string;
using std::cout;

class Locatar
{
	// clasa din layerul domain
	// contine 4 campuri caracteristice iar apartament este folosit ca si id unic, fiecare camp are getter si setter, mai putin id-ul care are doar getter
private:
	int apartament;
	string proprietar;
	int suprafata;
	string tip;
public:
	Locatar() = default;
	/*
	 constructor de creere
	 date de intrare:
			apartament - int
			proprietatr - string
			suprafata - int
			tip - string
	 date de iesire:
			obiect de tip Locatar cu campurile corespunzatoare datelor de intrare intializate
	*/
	Locatar(int ap, const string pr, int s, const string t) :apartament{ ap }, proprietar{ pr }, suprafata{ s }, tip{ t }{
	};
	
	/*
	constructor de copiere
	semnaleaza cand se apeleaza tiparind un specific 
	*/
	Locatar(const Locatar& ot) :apartament{ ot.apartament }, proprietar{ ot.proprietar }, suprafata{ ot.suprafata }, tip{ ot.tip } {
	};

	int getApartament() const noexcept {
		return apartament;
	}

	string getProprietar() const  {
		return proprietar;
	}

	int getSuprafata() const noexcept {
		return suprafata;
	}

	string getTip() const {
		return tip;
	}

	void setProprietar(const string& pr) {
		proprietar = pr;
	}

	void setSuprafata(int s) noexcept {
		suprafata = s;
	}

	void setTip(const string& t) {
		tip = t;
	}
};

/*
Compara dupa suprafata
returneaza true daca l1.suprafata e mai mic decat l2.suprafata
*/
bool cmpSupr(const Locatar& l1, const Locatar& l2) noexcept;

/*
Compara dupa proprietar
returneaza true daca l1.proprietar e mai mic decat l2.proprietar
*/
bool cmpProp(const Locatar& l1, const Locatar& l2);