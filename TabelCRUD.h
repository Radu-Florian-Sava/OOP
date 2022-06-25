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

class TabelCRUD : public QWidget, public Observer {
private:
	ListaLocatari& lista;
	QTableWidget* lst;
	QPushButton* btn;
	QPushButton* btnRandom;

	void loadTable(const std::vector<Locatar>& locatari) {
		lst->clear();
		lst->setRowCount(locatari.size());
		lst->setColumnCount(4);
		for (int i = 0; i < locatari.size(); i++) {
			lst->setItem(i, 0, new QTableWidgetItem(QString::number(locatari[i].getApartament())));
			lst->setItem(i, 1, new QTableWidgetItem(locatari[i].getProprietar().c_str()));
			lst->setItem(i, 2, new QTableWidgetItem(QString::number(locatari[i].getSuprafata())));
			lst->setItem(i, 3, new QTableWidgetItem(locatari[i].getTip().c_str()));
		}
	}

	void initGUI() {
		this->setWindowTitle("Bloc");
		this->setWindowIcon(QIcon("OhYeah.png"));
		QVBoxLayout* ly = new QVBoxLayout;
		lst = new QTableWidget;
		ly->addWidget(lst);
		btn = new QPushButton("Goleste tabel");
		ly->addWidget(btn);

		btnRandom = new QPushButton("Umple tabel");
		ly->addWidget(btnRandom);
		setLayout(ly);
	}
	void connectSignals() {
		lista.addObserver(this);
		QObject::connect(btn, &QPushButton::clicked, [&]() {
			lista.goleste();
			loadTable(lista.lista());
			});
		QObject::connect(btnRandom, &QPushButton::clicked, [&]() {
			lista.umple();
			loadTable(lista.lista());
			});

	}
public:
	TabelCRUD(ListaLocatari &lista) :lista{ lista } {
		initGUI();
		connectSignals();
		loadTable(lista.lista());
	}

	void update() override {
		loadTable(lista.lista());
	}

	~TabelCRUD() {
		lista.removeObserver(this);
	}

};

