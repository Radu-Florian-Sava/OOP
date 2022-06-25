#include "UI.h"

#include "Locatar.h"
#include <iostream>
#include <string>

using std::cout;
using std::cin;

void UI::tipareste(const vector<Locatar>& locatari) {
	cout << "=========================================================================\n";
	cout << "Locatari:\n";
	for (const auto& l : locatari) {
		cout << ' ' << l.getApartament() << ' ' << l.getProprietar() << ' ' << l.getSuprafata() << ' '<<l.getTip() << '\n';
	}
}

void UI::adaugaUI() {
	string  prorpietar, tip;
	int apartament, suprafata;
	cout << "Dati adresa apartamentului:";
	cin >> apartament;
	cout << "Dati numele proprietarului:";
	cin >> prorpietar;
	cout << "Dati suprafata:";
	cin >> suprafata;
	cout << "Dati tipul apartamentului:";
	cin >> tip;
	serv.addLocatar(apartament, prorpietar, suprafata, tip);
	cout << "Adaugat cu succes\n";
}

void UI::modificaUI() {
	string  prorpietar, tip;
	int apartament, suprafata;
	cout << "Dati adresa apartamentului:";
	cin >> apartament;
	cout << "Dati numele noului proprietar:";
	cin >> prorpietar;
	cout << "Dati noua suprafata:";
	cin >> suprafata;
	cout << "Dati tipul noului apartament:";
	cin >> tip;
	serv.updateLocatar(apartament, prorpietar, suprafata, tip);
	cout << "Modificat cu succes\n";
}

void UI::stergeUI() {
	int apartament;
	cout << "Dati adresa apartamentului:";
	cin >> apartament;
	serv.deleteLocatar(apartament);
	cout << "Sters cu succes\n";
}

void UI::ladaugaUI() {
	int apartament;
	cout << "Dati adresa apartamentului:";
	cin >> apartament;
	serv.addLista(apartament);
	cout << "Lista a fost modificata cu succes\n";
}

void UI::lgolesteUI() {
	serv.golesteLista();
	cout << "Lista a fost golita cu succes!\n";
}

void UI::lgenUI() {
	int nr;
	cout << "Dati numarul de inregistrari:";
	cin >> nr;
	if (nr < 0)
		nr = 0;
	serv.genLista(nr);
	cout << "Lista a fost generata cu succes\n";
}

void UI::mapUI() {
	if (!serv.functieMap().empty())
	{
		cout << "=========================================================================\n";
		for (auto& it : serv.functieMap())
		{
			cout << it.second.first << " " << it.second.second << '\n';
		}
	}
}

void UI::exportUI() {
	string  nume;
	cout << "Dati numele fisierului de export:";
	cin >> nume;
	serv.exportLista(nume);
	cout << "Export realizat cu succes!\n";
}

void UI::undoUI() {
	serv.Undo();
	cout << "Undo realizat cu succes!\n";
}

void UI::redoUI() {
	serv.Redo();
	cout << "Redo realizat cu succes!\n";
}

void UI::citesteUI() {
	serv.importRepo("apartamente.txt");
	cout << "Citirea din fisier a fost finalizata cu succes!\n";
}

void UI::scrieUI() {
	serv.exportRepo("apartamente.txt");
	cout << "Scrierea in fisier a fost finalizata cu succes!\n";
}

void UI::run() {
	string tip;
	while (true) {

		cout << "=========================================================================\n";
		cout << "Meniu:\n";
		cout << "1 adauga\n2 modifica\n3 sterge\n4 tipareste\n5 sorteaza dupa proprietar\n6 sort dupa suprafata\n7 sorteaza dupa tip+suprafata\n8 filtrare suprafata\n9 filtrare tip\n10 adauga lista\n11 goleste lista\n12 genereaza lista\n13 exporta lista\n14 afisare map\n15 undo\n16 redo\n17 citire fisier\n18 scriere fisier\n0 iesire\n";
		cout << "=========================================================================\n";
		cout<<"Dati comanda : ";
		int cmd;
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaUI();
				break;
			case 2:
				modificaUI();
				break;
			case 3:
				stergeUI();
				break;
			case 4:
				tipareste(serv.getAll());
				break;
			case 5:
				tipareste(serv.sortByProprietar());
				break;
			case 6:
				tipareste(serv.sortBySuprafata());
				break;
			case 7:
				tipareste(serv.sortByTipSuprafata());
				break;
			case 8:
				cout << "Dati suprafata maxima:";
				int suprafata;
				cin >> suprafata;
				tipareste(serv.filtrareSuprafataMaiMica(suprafata));
				break;
			case 9:
				cout << "Dati tipul:";
				cin >> tip;
				tipareste(serv.filtrareTip(tip));
				break;
			case 10:
				ladaugaUI();
				break;
			case 11:
				lgolesteUI();
				break;
			case 12:
				lgenUI();
				break;
			case 13:
				exportUI();
				break;
			case 14:
				mapUI();
				break;
			case 15:
				undoUI();
				break;
			case 16:
				redoUI();
				break;
			case 17:
				citesteUI();
				break;
			case 18:
				scrieUI();
				break;
			case 0:
				return;
			default:
				cout << "Comanda invalida\n";
			}
		}
		catch (const RepoException& ex) {
			cout << ex << '\n';
		}
		catch (const ValidateException& ex) {
			cout << ex << '\n';
		}
	}
}