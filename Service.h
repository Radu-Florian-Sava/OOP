#pragma once

#include "Locatar.h"
#include "Repo.h"
#include "ExceptionRepo.h"
#include "AbstractRepo.h"
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <functional>
#include "Validator.h"
#include <memory>
#include "ListaLocatari.h"
#include <fstream>

using std::vector;
using std::map;
using std::pair;
using std::function;
using std::unique_ptr;

class Undo {
public:
	virtual void DoUndo() = 0;
	virtual void DoRedo() = 0;
	virtual ~Undo() = default;
};

class UndoAdd : public Undo {
	Locatar l;
	AbstractRepo& repo;
public:
	UndoAdd(AbstractRepo& repo, const Locatar& l) : repo{ repo }, l{ l } {}
	void DoUndo() override {
		repo.sterge(l);
	}
	void DoRedo() override {
		repo.adauga(l);
	}
};

class UndoDelete : public Undo {
	Locatar l;
	AbstractRepo& repo;
public:
	UndoDelete(AbstractRepo& repo, const Locatar& l) : repo{ repo }, l{ l } {}
	void DoUndo() override {
		repo.adauga(l);
	}
	void DoRedo() override {
		repo.sterge(l);
	}
};

class UndoUpdate : public Undo {
	string proprietar;
	int suprafata;
	string tip;
	Locatar l_nou;
	AbstractRepo& repo;
public:
	UndoUpdate(AbstractRepo& repo, string proprietar, int suprafata, string tip, const Locatar& l_nou) : repo{ repo }, proprietar{ proprietar }, suprafata{ suprafata }, tip{ tip }, l_nou{l_nou} {};
	void DoUndo() override {
		Locatar l(l_nou.getApartament(), proprietar, suprafata, tip);
		repo.modifica(l);
	}
	void DoRedo() override {
		repo.modifica(l_nou);
	}
};

class Service {
	AbstractRepo& rep;
	LocatarValidator& val;
	vector <unique_ptr<Undo>> undo;
	vector <unique_ptr<Undo>> redo;
	ListaLocatari lista_n;

	/*
	 Functie de sortare generala
	 maiMareF - functie care compara doua obiecte de tip Locatar, verifica daca are loc relatia mai mare
			  - poate fi orice functe (in afara clasei) care respecta signatura (returneaza bool are 2 parametrii Locatar)
			  - poate fi functie lambda (care nu capteaza nimic in capture list)
	 returneaza o lista sortata dupa criteriu dat ca paramatru
	*/
	//vector<Locatar> generalSort(bool (*maiMicF)(const Locatar&, const Locatar&));
	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar locatari care trec de filtru (fct(locatar)==true)
	*/
	vector<Locatar> filtreaza(function<bool(const Locatar&)> fct);
public:
	Service(AbstractRepo& rep, LocatarValidator& val) noexcept :rep{ rep }, val{ val }, lista_n{rep} {
	}

	//nu permitem copierea de obiecte Service
	Service(const Service& ot) = delete;

	/*
	 returneaza toti locatarii in ordinea in care au fost adaugati
	*/
	const vector<Locatar>& getAll() {
		return rep.getAll();
	}

	/*
	Adauga un nou locatar
	arunca exceptie daca: nu se poate salva, nu este valid
	*/
	void addLocatar(int apartament, const string& prorpietar, int suprafata, const string& tip);

	/*
	Modifica un locatar existent
	arunca exceptie daca: nu exista, nu este valid
	*/
	void updateLocatar(int apartament, const string& prorpietar, int suprafata, const string& tip);

	/*
	Sterge un locatar existent identificat dupa id(apartament)
	arunca exceptie daca: nu exista
	*/
	void deleteLocatar(int apartament);

	/*
	Sorteaza dupa proprietar
	*/
	vector<Locatar> sortByProprietar();

	/*
	Sorteaza dupa suprafata
	*/
	vector<Locatar> sortBySuprafata();

	/*
	Sorteaza dupa tip+suprafata
	*/
	vector<Locatar> sortByTipSuprafata();

	/*
	returneaza doar locatarii cu un aparament cu suprafata mai mica decat cea data
	*/
	vector<Locatar> filtrareSuprafataMaiMica(int suprafata);

	/*
	returneaza doar locatarii cu un apartament de un anumit tip
	*/
	vector<Locatar> filtrareTip(const string& tip);

	/*
	goleste lista de locatari notificati
	*/
	void golesteLista () noexcept;

	/*
	adauga un locatar in lista dupa numarul apartamnetului
	*/
	void addLista(int nr);

	/*
	genereaza lista dupa numarul de apartamente intordus, numar generat aleator
	*/
	void genLista(unsigned int nr);

	/*
	face salvarea intr-un fisier de tip .CSV
	*/
	void exportLista(string nume);

	/*
	returneaza o copie a listei
	*/
	ListaLocatari& getLista();

	/*
	metoda care creeaza un map ce contine perechea tip(cheie)-DTO(valoare), unde DTO este o pereche ce contine tipul si numarul sau de aparitii
	*/
     map<string, pair<string, int>> functieMap();

	 /*
	 metoda care realizeaza undo pe repository
	 */
     void Undo();

	 /*
	 metoda care realizeaza redo pe repository
	 */
	 void Redo();

	 /*
	 metoda care realizeaza scrie inregistrarile din repository in fisier(format CSV, extensie .txt)
	 */
	 void importRepo(const string&);

	 /*
	 metoda care realizeaza incarca inregistrarile in repository din fisier
	 */
	 void exportRepo(const string&);
	
};
/*
metoda care ruleaza testele service-ului
*/
void testService();
