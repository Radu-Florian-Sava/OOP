#include "saptamana_10_oop_gui.h"
#include <QtWidgets/QApplication>
#include "UI.h"
#include "Service.h"
#include "Repo.h"
#include "AbstractRepo.h"
#include "ExceptionRepo.h"
#include "validator.h"
#include "GUI.h"
#include "ListaCRUD.h"
#include "ListaDesenare.h"
#include <crtdbg.h>

void testAll() {
	// functie care ruleaza toate tesetele corespunzatoare claselor folosite
	// date de intrare: -
	// date de iesire: -
	testeRepo();
	testService();
	testValidator();
}

void adaugaCateva(Service& serv) {
	// functie care adauga inregistrari in repository
	// date de intrare: -
	// date de iesire: -
	serv.addLocatar(1, "Ionescu", 10, "inchiriat");
	serv.addLocatar(2, "Ionescu", 100, "inchiriat");
	serv.addLocatar(7, "Lupu", 50, "vanzare");
	serv.addLocatar(3, "Plesa", 70, "vanzare");
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
	testAll();
	Repo rep;
	LocatarValidator val;
	Service serv{ rep,val };
	//adaugaCateva(serv);
	const auto gui{ new GUI{ serv } };
	gui->show();

	const auto exit_code{ a.exec() };

	return exit_code;
}
