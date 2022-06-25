#pragma once

#include "Locatar.h"
#include "Service.h"
#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class TableModelView : public QAbstractTableModel {
private:
	vector<Locatar>& elems;
	bool visible;

public:
	TableModelView() = delete;

	TableModelView(vector<Locatar>& elems) :elems{ elems }, visible{ true } {

	}

	TableModelView(TableModelView& ot) = delete;

	TableModelView& operator=(TableModelView& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return (visible) ? (elems.size()) : (0);
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			font.setItalic(false);
			font.setBold(false);

			return font;
		}
		else if (role == Qt::BackgroundRole)
			return QBrush(Qt::white, Qt::SolidPattern);
		else if (role == Qt::DisplayRole)
		{
			if (orientation == Qt::Horizontal)
			{
				if (!section)
					return QString{ "Apartament" };
				else if (section == 1)
					return QString{ "Proprietar" };
				else if (section == 2)
					return QString{ "Suprafata" };
				else if (section == 3)
					return QString{ "Tip" };
			}
			else if (orientation == Qt::Vertical)
				return QString{ "%1" }.arg(section + 1);
		}

		return QVariant{};
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
		if (role == Qt::FontRole)
		{
			QFont font;
			font.setItalic(false);
			font.setBold(false);

			return font;
		}
		else if (role == Qt::BackgroundRole)
			return QBrush(Qt::white, Qt::SolidPattern);
		else if (role == Qt::TextAlignmentRole)
			return Qt::AlignHCenter;
		else if (role == Qt::DisplayRole)
		{
			qDebug() << "row: " << index.row() << " column: " << index.column();

			
			auto locatari{ elems};
			auto locatar{ locatari.at(index.row()) };

			if (!index.column())
				return QString(QString::number(locatar.getApartament()));
			else if (index.column() == 1)
				return QString(QString::fromStdString(locatar.getProprietar()));
			else if (index.column() == 2)
				return QString(QString::number(locatar.getSuprafata()));
			else if (index.column() == 3) 
				return QString(QString::fromStdString(locatar.getTip()));
		
		}
		else if (role == Qt::UserRole) {
			auto locatari{ elems };
			auto locatar{ locatari.at(index.row()) };

			const auto qapart{ QString::number(locatar.getApartament()) };
			const auto qowner{ QString(QString::fromStdString(locatar.getProprietar())) };
			const auto qarea{ QString::number(locatar.getSuprafata()) };
			const auto qtype{ QString::fromStdString(locatar.getTip()) };

			return QStringList{ qapart, qowner, qarea, qtype };
		}

		return QVariant();
	}

	void setTable() {
		emit layoutChanged();
	}

	void setVisible(const bool value) {
		this->visible = value; // visible = value;
		this->setTable(); 
	}

	~TableModelView() = default;
};