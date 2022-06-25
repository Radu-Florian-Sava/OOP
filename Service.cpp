#include "Service.h"
#include <functional>
#include <algorithm>
#include <assert.h>
#include <random>
#include <stdlib.h>
#include <memory>
#include <fstream>
#include <sstream>
#include <chrono>

using std::make_unique;
using std::stringstream;

//vector<Locatar> Service::generalSort(bool(*maiMicF)(const Locatar&, const Locatar&)){
//	vector<Locatar> v{ rep.getAll() };//fac o copie	
//	for (size_t i = 0; i < v.size(); i++) {
//		for (size_t j = i + 1; j < v.size(); j++) {
//			if (!maiMicF(v.at(i), v.at(j))) {
//				//interschimbam
//				Locatar aux = v.at(i);
//				v.at(i) = v.at(j);
//				v.at(j) = aux;
//			}
//		}
//	}
//	return v;
//}

/*
Adauga un nou locatar
arunca exceptie daca: nu se poate salva, nu este valid
*/
void Service::addLocatar(int apartament, const string& prorpietar, int suprafata, const string& tip) {
	Locatar l{ apartament, prorpietar, suprafata, tip};
	val.valideaza(l);
	rep.adauga(l);
	undo.push_back(make_unique<UndoAdd>(rep, l));
	redo.clear();
}
/*
Modifica un locatar existent
arunca exceptie daca: nu exista, nu este valid
*/
void Service::updateLocatar(int apartament, const string& prorpietar, int suprafata, const string& tip) {
	Locatar l{ apartament, prorpietar, suprafata, tip };
	val.valideaza(l);
	for (auto& el : rep.getAll())
		if (el.getApartament() == l.getApartament()) {
			undo.push_back(make_unique<UndoUpdate>(rep, el.getProprietar(),el.getSuprafata(),el.getTip(),l));
			redo.clear();
			break;}
	rep.modifica(l);
}
/*
Sterge un locatar existent
arunca exceptie daca: nu exista
*/
void Service::deleteLocatar(int apartament) {
	Locatar l{ apartament,"a",1,"a" };
	for (auto& el : rep.getAll())
		if (el.getApartament() == apartament) {
			undo.push_back(make_unique<UndoDelete>(rep, el));
			break;
		}
	redo.clear();
	rep.sterge(l);
}

/*
Sorteaza dupa prorpietar
*/
vector<Locatar> Service::sortByProprietar() {
	vector<Locatar> v{ rep.getAll() };
	sort(v.begin(), v.end(), cmpProp);
	return v;
}

/*
Sorteaza dupa suprafata
*/
vector<Locatar> Service::sortBySuprafata() {
	vector<Locatar> v{ rep.getAll() };
	sort(v.begin(), v.end(), cmpSupr);
	return v;
}


/*
Sorteaza dupa tip+suprafata
*/
vector<Locatar> Service::sortByTipSuprafata() {
	vector<Locatar> v{ rep.getAll() };
	
	sort(v.begin(),v.end(),[](const Locatar& l1, const Locatar& l2) {
		if (l1.getTip() == l2.getTip()) {
			return l1.getSuprafata() < l2.getSuprafata();
		}
		return l1.getTip() < l2.getTip();
		});
		return v;
}

vector<Locatar> Service::filtreaza(function<bool(const Locatar&)> fct) {
	vector<Locatar> rez(rep.getAll().size());
	auto it=std::copy_if(rep.getAll().begin(),rep.getAll().end(),rez.begin(),fct);
	rez.resize(std::distance(rez.begin(), it));
	/*for (const auto& l : rep.getAll()) {
		if (fct(l)) {
			rez.push_back(l);
		}
	}*/
	return rez;
}

vector<Locatar> Service::filtrareSuprafataMaiMica(int suprafata) {
	return filtreaza([suprafata](const Locatar& l) noexcept{
		return l.getSuprafata() < suprafata;
		});
}

vector<Locatar> Service::filtrareTip(const string& tip) {
	return filtreaza([=](const Locatar& l) {
		return l.getTip() == tip;
		});
}


void Service::golesteLista () noexcept
{
	lista_n.goleste();
}

void Service::addLista(int nr)
{
	Locatar l{ nr, "a", 1, "a" };
	val.valideaza(l);
	lista_n.adauga(rep.cauta(l.getApartament()));
}

void Service::genLista(unsigned int nr)
{
	lista_n.umple(nr);
}

void Service::exportLista( string nume)
{
	val.valideaza(Locatar{ 1,nume,1,nume });
	nume = nume + ".csv";
	FILE* f = fopen(nume.c_str(), "w");
	for (auto& l : lista_n.lista())
	{
		fprintf(f, "%d,%s,%d,%s\n", l.getApartament(), l.getProprietar().c_str(), l.getSuprafata(), l.getTip().c_str());
	}
	fclose(f);

}

ListaLocatari& Service::getLista()
{
	return lista_n;
}

 map<string, pair<string, int>> Service::functieMap() {
	map<string, pair<string, int>> dictionar;
	for (auto& l : rep.getAll())
	{
		if (dictionar.find(l.getTip()) != dictionar.end())
		{
			dictionar.find(l.getTip())->second.second++;
		}
		else
		{
			pair<string, int> p(l.getTip(), 1);
			dictionar.emplace(l.getTip(),p);
		}
	}
	return dictionar;
}

 void Service::Undo() {
	 if (undo.empty()) {
		 vector <string> messages;
		 messages.push_back("Nu mai exista operatii!");
		 if(messages.size()>0)
			throw ValidateException(messages);}
	 undo.back()->DoUndo();
	 redo.push_back(move(undo.back()));
	 undo.pop_back();
 }

 void Service::Redo() {
	 if (redo.size() == 0) return;
	 redo.back()->DoRedo();
	 undo.push_back(move(redo.back()));
	 redo.pop_back();
 }
 void Service::importRepo(const string& numeFisier) {
	 std::ifstream citeste(numeFisier);
	 string linie;
	 stringstream s;
	 while (getline(citeste,linie)) {
		 s=stringstream(linie.substr(0, linie.find(",")));
		 int apartament;
		 s >> apartament;
		 linie = linie.substr(linie.find(",")+1);
		 string proprietar = linie.substr(0, linie.find(","));
		 linie = linie.substr(linie.find(",") + 1);
		 s = stringstream(linie.substr(0, linie.find(",")));
		 int suprafata;
		 s >> suprafata;
		 linie = linie.substr(linie.find(",") + 1);
		 string tip = linie.substr(0, linie.find(","));
		 Locatar l(apartament, proprietar, suprafata, tip);
		 rep.adauga(l);
	 }
	 citeste.close();
 }

 void Service::exportRepo(const string& numeFisier) {
	 remove(numeFisier.c_str());
	 std::ofstream scrie(numeFisier);
	 for (auto& el : rep.getAll()) {
		 scrie << el.getApartament() << ",";
		 scrie << el.getProprietar() << ",";
		 scrie << el.getSuprafata() << ",";
		 scrie << el.getTip() << "\n";
	 }
	 scrie.close();
 }


void testAdaugaService() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 6,"a");
	assert(serv.getAll().size() == 1);

	//adaug ceva invalid
	try {
		serv.addLocatar(-1, "", -1,"");
		assert(false);}
	catch (ValidateException&) {
		assert(true);
	}
	//incerc sa adaug ceva ce exista deja
	try {
		serv.addLocatar(1, "a", -1,"a");
		assert(false);}
	catch (ValidateException&) {
		assert(true);
	}
}

void testModificaService() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 6, "a");
	assert(serv.getAll().size() == 1);

	//adaug ceva invalid
	try {
		serv.updateLocatar(1, "", -1, "");
		assert(false);}
	catch (ValidateException&) {
		assert(true);
	}
	serv.updateLocatar(1, "b", 4, "c");
	assert(serv.getAll().at(0).getProprietar() == "b");
	assert(serv.getAll().at(0).getTip() == "c");
	assert(serv.getAll().at(0).getSuprafata() == 4);
}

void testStergeService() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 6, "a");
	assert(serv.getAll().size() == 1);
	//incerc sa adaug ceva ce exista deja
	try {
		serv.deleteLocatar(2);
		assert(false);}
	catch (const RepoException&) {
		assert(true);
	}
	serv.deleteLocatar(1);
	assert(rep.getAll().size() == 0);
	try {
		serv.deleteLocatar(0);
		assert(false);}
	catch (const RepoException&) {
		assert(true);
	}
}

void testFiltrare() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 100,"a");
	serv.addLocatar(2, "a", 200,"a");
	serv.addLocatar(3, "a", 300,"b");
	assert(serv.filtrareTip("a").size() == 2);
	assert(serv.filtrareTip("b").size() == 1);
	assert(serv.filtrareSuprafataMaiMica(150).size() == 1);
	assert(serv.filtrareSuprafataMaiMica(50).size() == 0);
	assert(serv.filtrareSuprafataMaiMica(300).size() == 2);
}

void testSortare() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(7, "z", 6,"z");
	serv.addLocatar(2, "a", 60,"c");
	serv.addLocatar(3, "a", 600,"c");

	auto firstP{ serv.sortByProprietar().at(0) };
	assert(firstP.getProprietar() == "a");

	firstP = serv.sortBySuprafata().at(0);
	assert(firstP.getSuprafata() == 6);

	firstP = serv.sortByTipSuprafata().at(0);
	assert(firstP.getSuprafata() == 60);

}

void testLista()
{
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 100, "a");
	serv.addLocatar(2, "a", 200, "a");
	serv.addLocatar(3, "a", 300, "b");
	serv.addLista(1);
	assert(serv.getLista().size() == 1);
	assert(serv.getLista().at(0).getSuprafata() == 100);
	serv.genLista(3);
	assert(serv.getLista().size() == 3);
	string nume{ "export" };
	serv.exportLista(nume);
	serv.golesteLista();
	assert(serv.getLista().size() == 0);
	serv.exportLista(nume);
	serv.genLista(188);
	assert(serv.getLista().size() == 3);
}

void testMap() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 100, "a");
	serv.addLocatar(2, "a", 200, "a");
	serv.addLocatar(3, "a", 300, "b");
	assert(serv.functieMap().at("a").first=="a");
	assert(serv.functieMap().at("a").second == 2);
	assert(serv.functieMap().at("b").first == "b");
	assert(serv.functieMap().at("b").second == 1);
}

void testUndo() {

	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 6, "a");
	serv.Undo();
	assert(serv.getAll().size() == 0);
	serv.Redo();
	assert(serv.getAll().size() == 1);
	assert(serv.getAll().at(0).getApartament() == 1);
	assert(serv.getAll().at(0).getProprietar() == "a");
	assert(serv.getAll().at(0).getSuprafata() == 6);
	assert(serv.getAll().at(0).getTip() == "a");
	serv.deleteLocatar(1);
	serv.Undo();
	assert(serv.getAll().size() == 1);
	assert(serv.getAll().at(0).getApartament() == 1);
	assert(serv.getAll().at(0).getProprietar() == "a");
	assert(serv.getAll().at(0).getSuprafata() == 6);
	assert(serv.getAll().at(0).getTip() == "a");
	serv.Redo();
	assert(serv.getAll().size() == 0);
	serv.Undo();
	serv.updateLocatar(1, "abcd", 500, "efgh");
	serv.Undo();
	serv.Redo();
	serv.Undo();
	assert(serv.getAll().size() == 1);
	assert(serv.getAll().at(0).getApartament() == 1);
	assert(serv.getAll().at(0).getProprietar() == "a");
	assert(serv.getAll().at(0).getSuprafata() == 6);
	assert(serv.getAll().at(0).getTip() == "a");
	serv.Undo();
	assert(serv.getAll().size() == 0);
	try {
		serv.Undo();
		assert(false);}
	catch (const ValidateException&) {
		assert(true);
	}
}

void testImportExport() {
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	serv.addLocatar(1, "a", 100, "a");
	serv.addLocatar(2, "a", 200, "a");
	serv.addLocatar(3, "a", 300, "b");
	serv.exportRepo("test.txt");
	for (int i = 1; i < 4; i++)
		serv.deleteLocatar(i);
	serv.importRepo("test.txt");
	assert(serv.getAll().size() == 3);

}

void testService() {
	testAdaugaService();
	testModificaService();
	testStergeService();
	testFiltrare();
	testSortare();
	testLista();
	testMap();
	testUndo();
	testImportExport();
}
