//#include "UI.h"
//#include "Service.h"
//#include "Repo.h"
//#include "AbstractRepo.h"
//#include "ExceptionRepo.h"
//#include "validator.h"
//#include <crtdbg.h>
//#define _CRTDBG_MAP_ALLOC
//
//void adaugaCateva(Service& serv) {
//	// functie care adauga inregistrari in repository
//	// date de intrare: -
//	// date de iesire: -
//	serv.addLocatar(1, "Ionescu", 10,"inchiriat");
//	serv.addLocatar(2, "Ionescu", 100,"inchiriat");
//	serv.addLocatar(7, "Lupu", 50,"vanzare");
//	serv.addLocatar(3, "Plesa", 70,"vanzare");
//}
//
//void testAll() {
//	// functie care ruleaza toate tesetele corespunzatoare claselor folosite
//	// date de intrare: -
//	// date de iesire: -
//	testeRepo();
//	testService();
//	testValidator();
//}
//
//int main() {
//		
//	testAll();
//	{Repo rep;
//	LocatarValidator val;
//	Service serv{ rep,val };
//	UI ui{ serv };
//	ui.run(); }
//	_CrtDumpMemoryLeaks();
//}