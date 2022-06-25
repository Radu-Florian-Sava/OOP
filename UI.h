#pragma once
#include "Service.h"
#include "Locatar.h"
class UI {
	Service& serv;
	/*
	Citeste datele de la tastatura si adauga Locatar
	arunca exceptie daca: nu se poate salva, nu e valid
	*/
	void adaugaUI();
	/*
	Citeste datele de la tastatura si modifica Locatar
	arunca exceptie daca: nu exista, nu e valid
	*/
	void modificaUI();
	/*
	Citeste datele de la tastatura si sterge Locatar
	arunca exceptie daca: nu exista
	*/
	void stergeUI();
	/*
	Tipareste o lista de locatari la consola
	*/
	void tipareste(const vector<Locatar>& locatari);

	/*
	adauga un apartament pe lista de notificari
	*/
	void ladaugaUI();

	/*
	goleste lista de notificari
	*/
	void lgolesteUI();

	/*
	genereaza lista de notificari
	*/
	void lgenUI();

	/*
	exporta lista de notificari
	*/
	void exportUI();

	/*
	metoda care afiseaza un map cu perechi cheie-valoare(string tip,(string tip-int count))
	*/
	void mapUI();

	/*
	metoda care apeleaza functia de undo din service
	*/
	void undoUI();

	/*
	metoda care apeleaza functia de redo din service
	*/
	void redoUI();

	/*
	metoda care apeleaza functia de citire din fisier din service
	*/
	void citesteUI();

	/*
	metoda care apeleaza functia de scriere in fisier din service
	*/
	void scrieUI();

public:
	UI(Service& serv) noexcept :serv{ serv } {
	}
	//nu permitem copierea obiectelor
	UI(const UI& ot) = delete;

	void run();
};