#pragma once

#include "Service.h"
#include "Observer.h"
#include "ListModelView.h"
#include "TableModelView.h"
#include <QtWidgets/qwidget.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qlistview.h>
#include <QtWidgets/qtableview.h>
#include <QtWidgets/qtablewidget.h>
#include <QtWidgets/qcheckbox.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qspinbox.h>

class GUI : public QWidget, public Observer{
private:
	// atribute/campuri si metode private


	Service& srv; // referinta la un obiect de clasa Service
	vector<Locatar> locs=srv.getAll();
	ListModelView* lst_model = new ListModelView(locs);
	TableModelView* tbl_model = new TableModelView(locs);

	QPushButton* btn_cos_crudgui = new QPushButton{ "ListaCRUD" };
	QPushButton* btn_cos_crudgui_v2 = new QPushButton{ "Tabel_CRUD" };
	QPushButton* btn_cos_readonlygui = new QPushButton{ "CosReadOnlyGUI" };
	QPushButton* btn_add = new QPushButton{ "Adaugare" };
	QPushButton* btn_modify = new QPushButton{ "Modificare" };
	QPushButton* btn_delete = new QPushButton{ "Stergere" };

	QPushButton* btn_file_read = new QPushButton{ "Import fisier" };
	QPushButton* btn_file_write = new QPushButton{ "Export fisier" };
	QPushButton* btn_type = new QPushButton{ "Afisare" };
	QPushButton* btn_undo = new QPushButton{ "Undo" };
	QPushButton* btn_redo = new QPushButton{ "Redo" };
	QPushButton* btn_lista = new QPushButton{ "Lista" };

	QPushButton* btn_clear = new QPushButton{ "Clear" };
	QPushButton* btn_exit = new QPushButton{ "Exit" };

	QPushButton* btn_sort_owner = new QPushButton{ "Sortare proprietar" };
	QPushButton* btn_sort_area = new QPushButton{ "Sortare suprafata" };
	QPushButton* btn_sort_type_plus_area = new QPushButton{ "Sortare tip + suprafata" };

	QPushButton* btn_filter_area= new QPushButton{ "Filtrare suprafata" };
	QPushButton* btn_filter_type = new QPushButton{ "Filtrare tip" };

	QLineEdit* apart_line_edit = new QLineEdit;
	QLineEdit* owner_line_edit = new QLineEdit;
	QLineEdit* area_line_edit = new QLineEdit;
	QLineEdit* type_line_edit = new QLineEdit;

	QLabel* filter_crt_label = new QLabel{ "Criteriu filtrare" };
	QLineEdit* filter_crt_line_edit = new QLineEdit;

	QListView* lst_apartment = new QListView();
	QTableView* tbl_apartment = new QTableView();
	QLineEdit* fisier_export_line_edit = new QLineEdit;

	QSpinBox* no_prods = new QSpinBox(nullptr);

	QPushButton* btn_golire_lista_locatari = new QPushButton{ "Golire" };
	QPushButton* btn_adaugare_lista_locatari = new QPushButton{ "Adaugare" };
	QPushButton* btn_tiparire_lista_locatari = new QPushButton{ "Tiparire" };
	QPushButton* btn_export_lista_locatari = new QPushButton{ "Export" };
	QPushButton* btn_generare_lista_locatari = new QPushButton{ "Generare" };

	QPushButton* btn_clear_lista = new QPushButton{ "Clear" };
	QPushButton* btn_close_lista = new QPushButton{ "Close" };

	QLineEdit* apart_list_line_edit = new QLineEdit;
	QLineEdit* owner_list_line_edit = new QLineEdit;
	QLineEdit* area_list_line_edit = new QLineEdit;
	QLineEdit* type_list_line_edit = new QLineEdit;

	QWidget* lista_widget = nullptr;
	QWidget* locatari_bloc_widget = nullptr;

	QListWidget* lst_locatari = new QListWidget();
	QTableWidget* tbl_locatari = new QTableWidget();

	unsigned number_of_undo;
	unsigned number_of_redo;

	// metode private

	void addLocatariToList(const vector<Locatar>& lista_locatari);
	void addLocatariToTable(const vector<Locatar>& lista_locatari);

	void initMeniuListaLocatariBloc();
	void connectSignalsListaLocatariBloc();
	void setInitialStateListaLocatariBloc();
	
	bool filteredGUI(const vector<Locatar>& filtered_list, const Locatar& prod);
	void showFilteredList(const vector<Locatar>& filtered_list);
	
	void addOwnerToList(const vector<Locatar>& locatari);
	void addOwnerToTable(const vector<Locatar>& locatari);

	void initGuiCmp();
	void connectSignals();
	void setInitialState();



public:
	// metode publice

	// constructor custom al unui obiect de clasa GUI
	GUI(Service& srv) : srv{ srv } {
		initGuiCmp();
		connectSignals();
		setInitialState();
		srv.getLista().addObserver(this);
	}
	
	void update() override {
		addLocatariToList(srv.getLista().lista());
		addLocatariToTable(srv.getLista().lista());
	}

	~GUI() {
		srv.getLista().removeObserver(this);
	}

};