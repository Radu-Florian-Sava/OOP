#pragma once

#include "Locatar.h"
#include "Service.h"
#include <QtWidgets/qabstractitemview.h>
#include <qdebug.h>

class ListModelView : public QAbstractListModel {
private:
	vector<Locatar>& elems;
	bool visible;

public:
	ListModelView() = delete;

	ListModelView(vector<Locatar>& elems) : elems{ elems}, visible{ true } {

	}

	ListModelView(ListModelView& ot) = delete;

	ListModelView& operator=(ListModelView& ot) = delete;

	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return (visible) ? (elems.size() + 1) : (0);
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 1;
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
			return Qt::AlignLeft;
		else if (role == Qt::UserRole)
		{
			auto locatari{elems };

			if (!index.row())
				return QVariant{};

			const auto locatar{ locatari.at(index.row() - (size_t)1) };

			const auto qapart{ QString::number(locatar.getApartament()) };
			const auto qowner{ QString(QString::fromStdString(locatar.getProprietar())) };
			const auto qarea{ QString::number(locatar.getSuprafata()) };
			const auto qtype{ QString::fromStdString(locatar.getTip()) };

			return QStringList{ qapart, qowner, qarea, qtype };
		}
		else if (role == Qt::DisplayRole)
		{
			qDebug() << "row: " << index.row();

			auto locatari{ elems };

			if (!index.row())
				return QString("Locatarii :");

			const auto locatar{ locatari.at(index.row() - (size_t)1) };

			const auto qapart{ QString::number(locatar.getApartament()) };
			const auto qowner{ QString(QString::fromStdString(locatar.getProprietar())) };
			const auto qarea{ QString::number(locatar.getSuprafata()) };
			const auto qtype{ QString::fromStdString(locatar.getTip()) };

			return QString::number(index.row()) + ": " + qapart + " | " + qowner + " | " + qarea + " | " + qtype;
		}

		return QVariant();
	}

	void setList() {
		emit layoutChanged();
	}

	void setVisible(const bool value) {
		this->visible = value; 
		this->setList(); 					
	}

	~ListModelView() = default;
};