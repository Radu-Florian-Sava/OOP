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
#include <qpainter.h>

using std::to_string;
using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;	


class ListaDesenare : public QWidget, public Observer {
private:
	ListaLocatari& lista;
	mt19937 mt{ random_device{}() };
	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		QImage ohYeah("OhYeah.png");
		QImage ohYeet("OhYeet.png");
		const uniform_int_distribution<> dist_bin(0, 1);
		const uniform_int_distribution<> dist_x(0, width()-ohYeah.width());
		const uniform_int_distribution<> dist_y(0, height()-ohYeah.height());
		const uniform_int_distribution<> dist_color(0, 255);
		for (auto& l : lista.lista()) {
			const int x{ dist_x(mt) }; 
			const int y{ dist_y(mt) }; 

			QPoint point{ x, y };
			if (!dist_bin(mt))
				p.drawImage(point, ohYeah);
			else
				p.drawImage(point,ohYeet);
		}
	}

public:
	ListaDesenare(ListaLocatari& lista) : lista{ lista } {
		lista.addObserver(this);
		this->setWindowTitle("Bloc");
		this->setWindowIcon(QIcon("OhYeah.png"));
	}

	void update() override {
		repaint();
	}

	~ListaDesenare() {
		lista.removeObserver(this);
	}

};
