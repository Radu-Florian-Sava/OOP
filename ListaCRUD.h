#pragma once
#include <qwidget.h>
#include <qtimer.h>
#include <QtWidgets/QHBoxLayout>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qtablewidget.h>
#include <qstring.h>
#include <qlabel.h>
#include <vector>
#include "ListaLocatari.h"
#include "Observer.h"
#include <string>

using std::to_string;

class ListaCRUD : public QWidget, public Observer {
private:
	ListaLocatari& lista;
	QListWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;
	void loadList(const std::vector<Locatar>& locatari) {
		lst->clear();
		for (auto& l : locatari) {
			lst->addItem(QString::fromStdString(to_string(l.getApartament()) + " " + l.getProprietar() + " " + to_string(l.getSuprafata())+" "+l.getTip()));
		}
	}
	void initGUI() {
		this->setWindowTitle("Bloc");
		this->setWindowIcon(QIcon("OhYeah.png"));
		QVBoxLayout* ly = new QVBoxLayout;
		lst = new QListWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Goleste lista");
		ly->addWidget(btn);

		btnRandom = new QPushButton("Umple lista");
		ly->addWidget(btnRandom);
		setLayout(ly);
	}
	void connectSignals() {
		lista.addObserver(this);
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			lista.goleste();
			loadList(lista.lista());
			});
		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			lista.umple();
			loadList(lista.lista());
			});
	}
public:
	ListaCRUD(ListaLocatari& lista) : lista{ lista } {
		initGUI();
		connectSignals();
		loadList(lista.lista());
	}

	void update() override {
		loadList(lista.lista());
	}

	~ListaCRUD() {
		lista.removeObserver(this);
	}

};
