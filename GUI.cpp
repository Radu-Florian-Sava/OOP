#include "GUI.h"
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qmessagebox.h>
#include <qdebug.h>
#include "ListaCRUD.h"
#include "TabelCRUD.h"
#include "ListaDesenare.h"

using std::to_string;

void GUI::initMeniuListaLocatariBloc()
{
	lista_widget = new QWidget{};
	lista_widget->setWindowTitle("Lista locatarilor din bloc selectati");

	QVBoxLayout* ly = new QVBoxLayout;

	lista_widget->setLayout(ly);

	QHBoxLayout* upper_ly = new QHBoxLayout;

	QLabel* title_lbl = new QLabel;
	title_lbl->setText("Meniu lista");
	title_lbl->setAlignment(Qt::AlignHCenter);

	upper_ly->addWidget(title_lbl);

	ly->addLayout(upper_ly);

	QHBoxLayout* lower_ly = new QHBoxLayout;

	QVBoxLayout* left_ly = new QVBoxLayout;

	QLabel* cos_lst_lbl = new QLabel;
	cos_lst_lbl->setText("Lista cu locatarii selectati");
	cos_lst_lbl->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(cos_lst_lbl);
	left_ly->addWidget(lst_locatari);

	QLabel* cos_tbl_lbl = new QLabel;
	cos_tbl_lbl->setText("Tabel cu locatarii selectati");
	cos_tbl_lbl->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(cos_tbl_lbl);
	left_ly->addWidget(tbl_locatari);

	lower_ly->addLayout(left_ly);

	QVBoxLayout* right_ly = new QVBoxLayout;

	QLabel* produs_cos_lbl = new QLabel;
	produs_cos_lbl->setText("Despre locatari");
	produs_cos_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(produs_cos_lbl);

	QFormLayout* form_ly_1 = new QFormLayout;

	QLabel* apart_list_label = new QLabel{ "Apartament" };
	QLabel* owner_list_label = new QLabel{ "Proprietar" };
	QLabel* area_list_label = new QLabel{ "Suprafata" };
	QLabel* type_list_label = new QLabel{ "Tip" };

	owner_list_line_edit->setReadOnly(true);
	area_list_line_edit->setReadOnly(true);
	type_list_line_edit->setReadOnly(true);

	form_ly_1->addRow(apart_list_label, apart_list_line_edit);
	form_ly_1->addRow(owner_list_label, owner_list_line_edit);
	form_ly_1->addRow(area_list_label, area_list_line_edit);
	form_ly_1->addRow(type_list_label, type_list_line_edit);

	right_ly->addLayout(form_ly_1);
	right_ly->addStretch();

	QLabel* lbl_info_cos = new QLabel;
	lbl_info_cos->setText("Locatari");
	lbl_info_cos->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(lbl_info_cos);

	QLabel* options_lbl = new QLabel;
	options_lbl->setText("Optiuni lista de locatari");
	options_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_lbl);

	QHBoxLayout* btns_ly_1 = new QHBoxLayout;

	btns_ly_1->addWidget(btn_golire_lista_locatari);
	btns_ly_1->addWidget(btn_adaugare_lista_locatari);
	btns_ly_1->addWidget(btn_tiparire_lista_locatari);

	right_ly->addLayout(btns_ly_1);
	
	QLabel* options_generare_lbl = new QLabel;
	options_generare_lbl->setText("Optiuni de generare a listei de locatari");
	options_generare_lbl->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(options_generare_lbl);

	QHBoxLayout* generare_ly = new QHBoxLayout;

	QLabel* no_prods_generare_lbl = new QLabel;
	no_prods_generare_lbl->setText("Numar de locatari");

	generare_ly->addWidget(no_prods_generare_lbl);

	no_prods->setMinimum(0);
	no_prods->setMaximum(500);
	generare_ly->addWidget(no_prods);

	right_ly->addLayout(generare_ly);

	right_ly->addWidget(btn_generare_lista_locatari);

	QFormLayout* export_form_ly = new QFormLayout;

	QLabel* fisier_export_label = new QLabel{ "Nume fisier export" };

	export_form_ly->addRow(fisier_export_label, fisier_export_line_edit);

	right_ly->addLayout(export_form_ly);

	QLabel* lbl_export = new QLabel{ "Fisier Export CSV" };

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_export_lista_locatari);

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_clear_lista);
	btns_ly_3->addWidget(btn_close_lista);

	right_ly->addLayout(btns_ly_3);

	lower_ly->addLayout(right_ly);

	ly->addLayout(lower_ly);

	lista_widget->show();
}

void GUI::connectSignalsListaLocatariBloc()
{
	QObject::connect(lst_locatari, &QListWidget::itemSelectionChanged, this, [&]() {
		
		auto sel{ lst_locatari->selectedItems() };
		if (sel.isEmpty())
		{
			apart_list_line_edit->setText("");
			owner_list_line_edit->setText("");
			area_list_line_edit->setText("");
			type_list_line_edit->setText("");
		}
		else {
			const auto lst{ sel.at(0)->data(Qt::UserRole).toStringList() };
			
			if (lst.size() != 4)
				return;

			apart_list_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			owner_list_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			area_list_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			type_list_line_edit->setText(lst.at(3).toLocal8Bit().constData());
		}
		});

	QObject::connect(tbl_locatari, &QTableWidget::itemSelectionChanged, this, [&]() {
		auto sel{ tbl_locatari->selectedItems() };

		if (sel.isEmpty()) 
		{
			apart_list_line_edit->setText("");
			owner_list_line_edit->setText("");
			area_list_line_edit->setText("");
			type_list_line_edit->setText("");
		}
		else {
			const QStringList lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			apart_list_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			owner_list_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			area_list_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			type_list_line_edit->setText(lst.at(3).toLocal8Bit().constData());
		}
		});

	QObject::connect(btn_adaugare_lista_locatari, &QPushButton::clicked, this, [&]() {
		const auto apartament{ apart_list_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.addLista(apartament.toInt());
			btn_golire_lista_locatari->setDisabled(false);
			msg->setText("Locatar adaugat in lista!");

			const auto& lista_locatari{ srv.getLista().lista() };

			addLocatariToList(lista_locatari);
			addLocatariToTable(lista_locatari);
		
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}
		catch (const ValidateException& ve) {
			std::stringstream mesaj;
			mesaj << ve;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}

		msg->show();

		});

	QObject::connect(btn_golire_lista_locatari, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa goliti lista de locatari?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		QMessageBox* msg = new QMessageBox;

		srv.golesteLista();
		btn_golire_lista_locatari->setDisabled(true);

		msg->setText("Golire efectuata");
        msg->show();

		const auto& lista_locatari{ srv.getLista().lista() };

		addLocatariToList(lista_locatari);
		addLocatariToTable(lista_locatari);

		});

	QObject::connect(btn_tiparire_lista_locatari, &QPushButton::clicked, this, [&]() {
			const auto& lista_locatari{ srv.getLista().lista() };

			addLocatariToList(lista_locatari);
			addLocatariToTable(lista_locatari);
		
		});

	QObject::connect(btn_generare_lista_locatari, &QPushButton::clicked, this, [&]() {
		const auto number{ no_prods->text() };

		QMessageBox* msg = new QMessageBox;

		try {
			srv.genLista(number.toInt());
			btn_golire_lista_locatari->setDisabled(false);

			msg->setText("Generare realizata cu succes");

			const auto& lista_locatari{ srv.getLista().lista() };

			addLocatariToList(lista_locatari);
			addLocatariToTable(lista_locatari);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}

		msg->show();

		});
	QObject::connect(btn_export_lista_locatari, &QPushButton::clicked, this, [&]() {
		const auto filename{ fisier_export_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		srv.exportLista(filename.toStdString());
		msg->show();

		});

	QObject::connect(btn_clear_lista, &QPushButton::clicked, this, [&]() {
		lst_locatari->clear();
		tbl_locatari->clear();

		tbl_locatari->setHorizontalHeaderLabels({ "Apartament", "Proprietar", "Suprafata", "Tip" });

		const auto& lista_locatari{ srv.getLista().lista() };

		addLocatariToList(lista_locatari);
		addLocatariToTable(lista_locatari);

		});

	QObject::connect(btn_close_lista, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa inchideti fereastra curenta?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			lista_widget->close();
			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}

		});
}

void GUI::addLocatariToList(const vector<Locatar>& lista)
{
	lst_locatari->clear();

	auto idx{ 0 };

	for (const auto& locatar : lista)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Locatarii de pe lista :" };
			lst_locatari->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_apart{ to_string(locatar.getApartament()) };
		auto str_owner{ locatar.getProprietar() };
		auto str_area{ to_string(locatar.getSuprafata()) };
		auto str_type{ locatar.getTip() };
		const auto str_locatar{ str_apart + sep + str_owner + sep + str_area + sep + str_type };

		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(str_locatar) };

		const auto q_str_name{ QString::fromStdString(str_apart) };
		const auto q_str_type{ QString::fromStdString(str_owner) };
		const auto q_str_price{ QString::fromStdString(str_area) };
		const auto q_str_producer{ QString::fromStdString(str_type) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		lst_locatari->addItem(item);
	}
}

void GUI::addLocatariToTable(const vector<Locatar>& lista)
{
	tbl_locatari->clear();

	auto rows{ (int)lista.size() };
	auto cols{ 4 };

	tbl_locatari->setRowCount(rows);
	tbl_locatari->setColumnCount(cols);

	tbl_locatari->setHorizontalHeaderLabels({ "Apartament","Proprietar","Suprafata","Tip" });

	auto row{ 0 };

	for (const auto& locatar : lista)
	{
		const auto q_str_apart{ QString::fromStdString(to_string(locatar.getApartament())) };
		const auto q_str_owner{ QString::fromStdString(locatar.getProprietar()) };
		const auto q_str_area{ QString::fromStdString(to_string(locatar.getSuprafata())) };
		const auto q_str_type{ QString::fromStdString(locatar.getTip()) };

		const QStringList q_string_list{ q_str_apart,  q_str_owner, q_str_area, q_str_type };

		QTableWidgetItem* apart_item = new QTableWidgetItem(QString::number(locatar.getApartament()));
		apart_item->setTextAlignment(Qt::AlignHCenter);
		apart_item->setData(Qt::UserRole, QStringList(q_string_list));
		apart_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* owner_item = new QTableWidgetItem(QString::fromStdString(locatar.getProprietar()));
		owner_item->setTextAlignment(Qt::AlignHCenter);
		owner_item->setData(Qt::UserRole, QStringList(q_string_list));
		owner_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* area_item = new QTableWidgetItem(QString::number(locatar.getSuprafata()));
		area_item->setTextAlignment(Qt::AlignHCenter);
		area_item->setData(Qt::UserRole, QStringList(q_string_list));
		area_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(locatar.getTip()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));
		type_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		tbl_locatari->setItem(row, 0, apart_item);
		tbl_locatari->setItem(row, 1, owner_item);
		tbl_locatari->setItem(row, 2, area_item);
		tbl_locatari->setItem(row, 3, type_item);
		++row;
	}
}

void GUI::setInitialStateListaLocatariBloc()
{
		const auto& lista_locatari{ srv.getLista().lista() };

		addLocatariToList(lista_locatari);
		addLocatariToTable(lista_locatari);
}

void GUI::initGuiCmp()
{
	this->setWindowTitle("Bloc");
	this->setWindowIcon(QIcon("OhYeah.png"));


	QHBoxLayout* main_ly = new QHBoxLayout;
	setLayout(main_ly);

	QVBoxLayout* left_ly = new QVBoxLayout;

	QLabel* lbl_products = new QLabel{ "Locatari ai blocului:" };
	lbl_products->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(lbl_products);

	QHBoxLayout* locatari_show = new QHBoxLayout;

	lst_apartment->setModel(lst_model);
	tbl_apartment->setModel(tbl_model);
	locatari_show->addWidget(lst_apartment);
	locatari_show->addWidget(tbl_apartment);

	left_ly->addLayout(locatari_show);

	//left_ly->addStretch();

	QLabel* sort = new QLabel{ "Optiuni sortare" };
	sort->setAlignment(Qt::AlignHCenter);

	left_ly->addWidget(sort);

	QHBoxLayout* btns_sort_ly = new QHBoxLayout;

	btns_sort_ly->addWidget(btn_sort_owner);
	//btns_sort_ly->addStretch();

	btns_sort_ly->addWidget(btn_sort_area);
	//btns_sort_ly->addStretch();

	btns_sort_ly->addWidget(btn_sort_type_plus_area);
	//btns_sort_ly->addStretch();

	left_ly->addLayout(btns_sort_ly);
	//left_ly->addStretch();

	QLabel* filter = new QLabel{ "Optiuni filtrare" };
	filter->setAlignment(Qt::AlignHCenter);
	left_ly->addWidget(filter);

	QFormLayout* filter_form_ly = new QFormLayout;

	QLabel* filter_crt_label = new QLabel{ "Introduceti datele de comparat pentru filtrare:" };

	filter_form_ly->addRow(filter_crt_label, filter_crt_line_edit);

	left_ly->addLayout(filter_form_ly);

	QHBoxLayout* btns_filter_ly = new QHBoxLayout;

	btns_filter_ly->addWidget(btn_filter_area);
	//btns_filter_ly->addStretch();

	btns_filter_ly->addWidget(btn_filter_type);
	//btns_filter_ly->addStretch();

	left_ly->addLayout(btns_filter_ly);

	main_ly->addLayout(left_ly);

	// main_ly->addStretch();

	QVBoxLayout* right_ly = new QVBoxLayout;

	main_ly->addLayout(right_ly);

	QLabel* products_label = new QLabel{ "Informatii locatari" };
	products_label->setAlignment(Qt::AlignHCenter);

	right_ly->addWidget(products_label);

	QFormLayout* form_ly = new QFormLayout;

	QLabel* apart_label = new QLabel{ "Apartament" };
	QLabel* owner_label = new QLabel{ "Proprietar" };
	QLabel* area_label = new QLabel{ "Suprafata" };
	QLabel* type_label = new QLabel{ "Tip" };

	apart_line_edit->setText("");
	owner_line_edit->setText("");
	area_line_edit->setText("");
	type_line_edit->setText("");

	form_ly->addRow(apart_label, apart_line_edit);
	form_ly->addRow(owner_label, owner_line_edit);
	form_ly->addRow(area_label, area_line_edit);
	form_ly->addRow(type_label, type_line_edit);
	
	right_ly->addLayout(form_ly);

	right_ly->addStretch();

	QLabel* general = new QLabel{ "Optiuni verificare locatari in bloc" };
	general->setAlignment(Qt::AlignHCenter);
	right_ly->addWidget(general);

	QHBoxLayout* btns_ly_1 = new QHBoxLayout;

	btns_ly_1->addWidget(btn_add);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_modify);
	//btns_ly_1->addStretch();

	btns_ly_1->addWidget(btn_delete);
	//btns_ly_1->addStretch();

	right_ly->addLayout(btns_ly_1);

	QHBoxLayout* btns_ly_2 = new QHBoxLayout;

	btns_ly_2->addWidget(btn_type);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_file_read);
	//btns_ly_2->addStretch();

	btns_ly_2->addWidget(btn_file_write);
	//btns_ly_2->addStretch();

	right_ly->addLayout(btns_ly_2);

	QHBoxLayout* btns_ly_3 = new QHBoxLayout;

	btns_ly_3->addWidget(btn_undo);
	//btns_ly_2->addStretch();

	btns_ly_3->addWidget(btn_redo);
	//btns_ly_2->addStretch();
	
	btns_ly_3->addWidget(btn_lista);
	//btns_ly_2->addStretch();

	right_ly->addLayout(btns_ly_3);

	QHBoxLayout* btns_ly_4 = new QHBoxLayout;

	//btns_ly_4->addWidget(btn_clear);
	//btns_ly_3->addStretch();

	btns_ly_4->addWidget(btn_exit);
	//btns_ly_3->addStretch

	right_ly->addLayout(btns_ly_4);

	QHBoxLayout* btns_ly_5 = new QHBoxLayout;

	btns_ly_5->addWidget(btn_cos_crudgui);
	//btns_ly_4->addStretch

	btns_ly_5->addWidget(btn_cos_readonlygui);
	//btns_ly_4->addStretch

	btns_ly_5->addWidget(btn_cos_crudgui_v2);
	//btns_ly_4->addStretch

	right_ly->addLayout(btns_ly_5);

}

bool GUI::filteredGUI(const vector<Locatar>& filtered_list, const Locatar& locatar)
{
	for (const auto& filtered_prod : filtered_list)
		if (locatar.getApartament() == filtered_prod.getApartament())
			return true;
	return false;
}

void GUI::showFilteredList(const vector<Locatar>& filtered_list)
{
	addOwnerToTable(filtered_list);
	addOwnerToList(filtered_list);
	//lst_apartment->clear();

	//auto idx{ 0 };
	///const auto& locatari{ srv.getAll() };

	/*for (const auto& locatar : locatari)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Locatarii blocului :" };
			lst_apartment->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_apart{ to_string(locatar.getApartament()) };
		auto str_owner{ locatar.getProprietar() };
		auto str_area{ to_string(locatar.getSuprafata()) };
		auto str_type{ locatar.getTip() };
		const auto str_product{ str_apart + sep + str_owner + sep + str_area + sep + str_type };

		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(str_product) };

		const auto q_str_apart{ QString::fromStdString(str_apart) };
		const auto q_str_owner{ QString::fromStdString(str_owner) };
		const auto q_str_area{ QString::fromStdString(str_area) };
		const auto q_str_type{ QString::fromStdString(str_type) };
		item->setData(Qt::UserRole, QStringList({ q_str_apart, q_str_owner, q_str_area, q_str_type }));

		if (filteredGUI(filtered_list, locatar))
			item->setBackground(Qt::green);
		else
			item->setBackground(Qt::red);

		lst_apartment->addItem(item);
	}*/

	/*if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Momentan nu exista locatari in bloc" };
		lst_apartment->addItem(item);
	}*/
}

void GUI::connectSignals()
{
	/*QObject::connect(lst_apartment, &QListWidget::itemSelectionChanged, this, [&]() {
		auto sel{ lst_apartment->selectedItems() };

		if (last_selected != nullptr) {
			last_selected->setBackground(Qt::white);
		}

		if (sel.isEmpty())
		{
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
		}
		else {
			const auto lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			apart_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			owner_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			area_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			type_line_edit->setText(lst.at(3).toLocal8Bit().constData());

			last_selected = lst_apartment->selectedItems().at(0);
			if(last_selected!=nullptr)
				last_selected->setBackground(Qt::darkGreen);
			QMessageBox* detalii = new QMessageBox;
			detalii->setWindowTitle("Detalii locatar");
			detalii->setText("Apartament: "+ apart_line_edit->text() + "\nProprietar: " + owner_line_edit->text() + "\nSuprafata: " + area_line_edit->text() +"\nTip: " +type_line_edit->text());
			detalii->show();
		}
		});
	*/

	QObject::connect(lst_apartment->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lst_apartment->selectionModel()->selectedIndexes().isEmpty()) {
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
			return;
		}
		auto selIndex = lst_apartment->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toStringList();
		
		apart_line_edit->setText(selIndex.at(0));
		owner_line_edit->setText(selIndex.at(1));
		area_line_edit->setText(selIndex.at(2));
		type_line_edit->setText(selIndex.at(3));

		QMessageBox* detalii = new QMessageBox;
		detalii->setWindowTitle("Detalii locatar");
		detalii->setText("Apartament: " + apart_line_edit->text() + "\nProprietar: " + owner_line_edit->text() + "\nSuprafata: " + area_line_edit->text() + "\nTip: " + type_line_edit->text());
		detalii->show();
		});

	QObject::connect(tbl_apartment->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl_apartment->selectionModel()->selectedIndexes().isEmpty()) {
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
			return;
		}
		auto selIndex = tbl_apartment->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toStringList();

		apart_line_edit->setText(selIndex.at(0));
		owner_line_edit->setText(selIndex.at(1));
		area_line_edit->setText(selIndex.at(2));
		type_line_edit->setText(selIndex.at(3));

		QMessageBox* detalii = new QMessageBox;
		detalii->setWindowTitle("Detalii locatar");
		detalii->setText("Apartament: " + apart_line_edit->text() + "\nProprietar: " + owner_line_edit->text() + "\nSuprafata: " + area_line_edit->text() + "\nTip: " + type_line_edit->text());
		detalii->show();

		});

	/*QObject::connect(tbl_apartment, &QTableWidget::itemSelectionChanged, this, [&]() {
		auto sel{ tbl_apartment->selectedItems() };

		if (sel.isEmpty()) 
		{
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
		}
		else {
			const QStringList lst{ sel.at(0)->data(Qt::UserRole).toStringList() };

			if (lst.size() != 4)
				return;

			apart_line_edit->setText(lst.at(0).toLocal8Bit().constData());
			owner_line_edit->setText(lst.at(1).toLocal8Bit().constData());
			area_line_edit->setText(lst.at(2).toLocal8Bit().constData());
			type_line_edit->setText(lst.at(3).toLocal8Bit().constData());
		}
		});
	*/
	QObject::connect(btn_add, &QPushButton::clicked, this, [&]() {
		const auto apart{ apart_line_edit->text() };
		const auto owner{ owner_line_edit->text() };
		const auto area{ area_line_edit->text() };
		const auto type{ type_line_edit->text() };

		QMessageBox* msg = new QMessageBox;
		const auto suprafata{ area.toInt() };
		const auto apartament{ apart.toInt() };

		try {
			srv.addLocatar(apartament, owner.toStdString(), suprafata, type.toStdString());

			++number_of_undo;
			if (!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			addOwnerToList(srv.getAll());
			addOwnerToTable(srv.getAll());
			msg->setText("Adaugarea s-a realizat cu succes!");
		}
		catch (const ValidateException& ve) {
			std::stringstream mesaj;
			mesaj << ve;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}

		msg->show();
		});

	QObject::connect(btn_modify, &QPushButton::clicked, this, [&]() {
		const auto apart{ apart_line_edit->text() };
		const auto owner{ owner_line_edit->text() };
		const auto area{ area_line_edit->text() };
		const auto type{ type_line_edit->text() };

		QMessageBox* msg = new QMessageBox;

		const auto suprafata{ area.toInt() };
		const auto apartament{ apart.toInt() };

		try {
			srv.updateLocatar(apartament, owner.toStdString(), suprafata, type.toStdString());

			++number_of_undo;
			if(!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			addOwnerToList(srv.getAll());
			addOwnerToTable(srv.getAll());

			msg->setText("Modificarea s-a realizat cu succes!");
		}
		catch (const ValidateException& ve) {
			std::stringstream mesaj;
			mesaj << ve;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}

		msg->show();
		});

	QObject::connect(btn_delete, &QPushButton::clicked, this, [&]() {
		
		const auto apart{ apart_line_edit->text() };
		QMessageBox* msg = new QMessageBox;

		const auto apartament{ apart.toInt() };
		try {
			srv.deleteLocatar(apartament);

			++number_of_undo;
			if (!btn_undo->isEnabled())
				btn_undo->setDisabled(false);

			addOwnerToList(srv.getAll());
			addOwnerToTable(srv.getAll());
			msg->setText("Stergerea s-a realizat cu succes!");

			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			msg->setText(QString::fromStdString(mesaj.str()));
		}
		
		msg->show();
		});

	QObject::connect(btn_sort_owner, &QPushButton::clicked, this, [&]() {
		
		try {

			const auto& sorted_products{ srv.sortByProprietar() };
			addOwnerToList(sorted_products);
			addOwnerToTable(sorted_products);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			addOwnerToList(vector<Locatar>());
			addOwnerToTable(vector<Locatar>());
		}
		

		});

	QObject::connect(btn_sort_area, &QPushButton::clicked, this, [&]() {
		
		try {


			const auto& sorted_products{ srv.sortBySuprafata() };

			addOwnerToList(sorted_products);
			addOwnerToTable(sorted_products);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			addOwnerToList(vector<Locatar>());
			addOwnerToTable(vector<Locatar>());
		}
		

		});

	QObject::connect(btn_sort_type_plus_area, &QPushButton::clicked, this, [&]() {
		
		try {


			const auto& sorted_products{ srv.sortByTipSuprafata() };

			addOwnerToList(sorted_products);
			addOwnerToTable(sorted_products);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			addOwnerToList(vector<Locatar>());
			addOwnerToTable(vector<Locatar>());
		}

		});

	QObject::connect(btn_filter_type, &QPushButton::clicked, this, [&]() {

		const auto filter{ filter_crt_line_edit->text() };

		try {
			const auto& filtered_list{ srv.filtrareTip(filter.toStdString()) };
			showFilteredList(filtered_list);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(mesaj.str()));
			msg->show();
		}

		});

	QObject::connect(btn_filter_area, &QPushButton::clicked, this, [&]() {
		
		const auto filter{ filter_crt_line_edit->text() };

		try {
			const auto& filtered_list{ srv.filtrareSuprafataMaiMica(filter.toInt()) };
			showFilteredList(filtered_list);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString( mesaj.str());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(mesaj.str()));
			msg->show();
		}
		
		});

	QObject::connect(btn_type, &QPushButton::clicked, this, [&]() {
		try {
			const auto& products{ srv.getAll() };
			
			addOwnerToList(products);
			addOwnerToTable(products);
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			addOwnerToList(vector<Locatar>());
			addOwnerToTable(vector<Locatar>());
		}
		});

	QObject::connect(btn_file_read, &QPushButton::clicked, this, [&]() {
		try {
			srv.importRepo("fisier_repo.txt");
			QMessageBox* msg = new QMessageBox;
			addOwnerToList(srv.getAll());
			addOwnerToTable(srv.getAll());
			msg->setText("Import realizat cu succes");
			msg->show();

		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(mesaj.str()));
			msg->show();
		}
		});

	QObject::connect(btn_file_write, &QPushButton::clicked, this, [&]() {
		try {
			srv.exportRepo("fisier_repo.txt");
			QMessageBox* msg = new QMessageBox;
			msg->setText("Export realizat cu succes");
			msg->show();
		}
		catch (const RepoException& re) {
			std::stringstream mesaj;
			mesaj << re;
			qDebug() << QString::fromStdString(mesaj.str());

			QMessageBox* msg = new QMessageBox;
			msg->setText(QString::fromStdString(mesaj.str()));
			msg->show();
		}
		});


	QObject::connect(btn_undo, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setWindowTitle("Undo");
		msg_box.setText("Operatia de undo va fi efectuata");
		msg_box.setInformativeText("Doriti sa continuati?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::Yes);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			try {
				srv.Undo();
				addOwnerToList(srv.getAll());
				addOwnerToTable(srv.getAll());
				--number_of_undo;
				++number_of_redo;
				if (!number_of_undo)
					btn_undo->setDisabled(true);
				if (!btn_redo->isEnabled())
					btn_redo->setDisabled(false);
			}
			catch (const ValidateException& ve) {
				std::stringstream mesaj;
				mesaj << ve;
				qDebug() << QString::fromStdString(mesaj.str());

				btn_undo->setDisabled(true);

				QMessageBox msg_dbg;
				msg_dbg.setText(QString::fromStdString(mesaj.str()));
				msg_dbg.exec();
			}

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_redo, &QPushButton::clicked, this, [&]() {
		QMessageBox msg_box;
		msg_box.setWindowTitle("Redo");
		msg_box.setText("Operatia de redo va fi efectuata");
		msg_box.setInformativeText("Doriti sa continuati?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::Yes);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			try {
				srv.Redo();
				addOwnerToList(srv.getAll());
				addOwnerToTable(srv.getAll());
				--number_of_redo;
				++number_of_undo;
				if (!number_of_redo)
					btn_redo->setDisabled(true);
				if (!btn_undo->isEnabled())
					btn_undo->setDisabled(false);
			}
			catch (const ValidateException& ve) {
				std::stringstream mesaj;
				mesaj << ve;
				qDebug() << QString::fromStdString(mesaj.str());

				btn_undo->setDisabled(true);

				QMessageBox msg_dbg;
				msg_dbg.setText(QString::fromStdString(mesaj.str()));
				msg_dbg.exec();
			}

			break;
		case QMessageBox::No:
			// No Save was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_lista, &QPushButton::clicked, this, [&]() {
		if (lista_widget == nullptr)
			connectSignalsListaLocatariBloc();
		else if (lista_widget->isEnabled())
		{
			lista_widget->setDisabled(true);
			lista_widget->close();
		}

		initMeniuListaLocatariBloc();
		setInitialStateListaLocatariBloc();
		});


	/*QObject::connect(btn_clear, &QPushButton::clicked, this, [&]() {
		lst_apartment->clear();
		tbl_apartment->clear();

		tbl_apartment->setHorizontalHeaderLabels({ "Apartamnet", "Proprietar", "Suprafata", "Tip" });
		});
	*/

	QObject::connect(btn_exit, &QPushButton::clicked, this, []() {
		QMessageBox msg_box;
		msg_box.setText("Sunteti sigur ca doriti sa iesiti din aplicatie?");
		msg_box.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
		msg_box.setDefaultButton(QMessageBox::No);

		const auto ret{ msg_box.exec() };

		switch (ret) {
		case QMessageBox::Yes:
			// Yes was clicked
			exit(0);
			break;
		case QMessageBox::No:
			// No was clicked
			break;
		case QMessageBox::Cancel:
			// Cancel was clicked
			break;
		}
		});

	QObject::connect(btn_cos_crudgui, &QPushButton::clicked, this, [&]() {
		ListaCRUD* lista_noua = new ListaCRUD(srv.getLista());
		lista_noua->show();
		});

	QObject::connect(btn_cos_readonlygui, &QPushButton::clicked, this, [&]() {
		ListaDesenare* lista_noua = new ListaDesenare(srv.getLista());
		lista_noua->show();
		});

	QObject::connect(btn_cos_crudgui_v2, &QPushButton::clicked, this, [&]() {
		TabelCRUD* tabel_nou = new TabelCRUD(srv.getLista());
		tabel_nou->show();
		});
}

void GUI::addOwnerToList(const vector<Locatar>& locatari)
{
	lst_model->~ListModelView();
	locs = locatari;
	lst_model = new ListModelView(locs);
	lst_apartment->setModel(lst_model);
	lst_model->setVisible(true);
	QObject::connect(lst_apartment->selectionModel(), &QItemSelectionModel::selectionChanged, [&]() {
		if (lst_apartment->selectionModel()->selectedIndexes().isEmpty()) {
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
			return;
		}
		auto selIndex = lst_apartment->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toStringList();

		apart_line_edit->setText(selIndex.at(0));
		owner_line_edit->setText(selIndex.at(1));
		area_line_edit->setText(selIndex.at(2));
		type_line_edit->setText(selIndex.at(3));

		QMessageBox* detalii = new QMessageBox;
		detalii->setWindowTitle("Detalii locatar");
		detalii->setText("Apartament: " + apart_line_edit->text() + "\nProprietar: " + owner_line_edit->text() + "\nSuprafata: " + area_line_edit->text() + "\nTip: " + type_line_edit->text());
		detalii->show();
		});

	QObject::connect(tbl_apartment->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl_apartment->selectionModel()->selectedIndexes().isEmpty()) {
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
			return;
		}
		auto selIndex = tbl_apartment->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toStringList();

		apart_line_edit->setText(selIndex.at(0));
		owner_line_edit->setText(selIndex.at(1));
		area_line_edit->setText(selIndex.at(2));
		type_line_edit->setText(selIndex.at(3));

		QMessageBox* detalii = new QMessageBox;
		detalii->setWindowTitle("Detalii locatar");
		detalii->setText("Apartament: " + apart_line_edit->text() + "\nProprietar: " + owner_line_edit->text() + "\nSuprafata: " + area_line_edit->text() + "\nTip: " + type_line_edit->text());
		detalii->show();

		});
	//lst_apartment->clear();
	
	/*last_selected = nullptr;
	auto idx{ 0 };

	for (const auto& locatar : locatari)
	{
		if (!idx)
		{
			QListWidgetItem* label_item = new QListWidgetItem{ "Locatarii blocului :" };
			lst_apartment->addItem(label_item);
		}

		++idx;

		const auto sep{ " | " };
		auto str_apart{ to_string(locatar.getApartament()) };
		auto str_owner{ locatar.getProprietar() };
		auto str_area{ to_string(locatar.getSuprafata()) };
		auto str_type{ locatar.getTip() };
		const auto str_locatar{ str_apart + sep + str_owner + sep + str_area + sep + str_type };

		QListWidgetItem* item = new QListWidgetItem{ QString::fromStdString(str_locatar) };

		const auto q_str_name{ QString::fromStdString(str_apart) };
		const auto q_str_type{ QString::fromStdString(str_owner) };
		const auto q_str_price{ QString::fromStdString(str_area) };
		const auto q_str_producer{ QString::fromStdString(str_type) };
		item->setData(Qt::UserRole, QStringList({ q_str_name, q_str_type, q_str_price, q_str_producer }));

		lst_apartment->addItem(item);
	}

	if (!idx)
	{
		QListWidgetItem* item = new QListWidgetItem{ "Momentan nu exista locatari in bloc" };
		lst_apartment->addItem(item);
	}*/
}

void GUI::addOwnerToTable(const vector<Locatar>& locatari)
{
	tbl_model->~TableModelView();
	locs = locatari;
	tbl_model = new TableModelView(locs);
	tbl_apartment->setModel(tbl_model);
	tbl_model->setVisible(true);
	QObject::connect(tbl_apartment->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
		if (tbl_apartment->selectionModel()->selectedIndexes().isEmpty()) {
			apart_line_edit->setText("");
			owner_line_edit->setText("");
			area_line_edit->setText("");
			type_line_edit->setText("");
			return;
		}
		auto selIndex = tbl_apartment->selectionModel()->selectedIndexes().at(0).data(Qt::UserRole).toStringList();

		apart_line_edit->setText(selIndex.at(0));
		owner_line_edit->setText(selIndex.at(1));
		area_line_edit->setText(selIndex.at(2));
		type_line_edit->setText(selIndex.at(3));

		QMessageBox* detalii = new QMessageBox;
		detalii->setWindowTitle("Detalii locatar");
		detalii->setText("Apartament: " + apart_line_edit->text() + "\nProprietar: " + owner_line_edit->text() + "\nSuprafata: " + area_line_edit->text() + "\nTip: " + type_line_edit->text());
		detalii->show();

		});
	/*tbl_apartment->clear();

	auto rows{ (int)locatari.size() };
	auto cols{ 4 };

	tbl_apartment->setRowCount(rows);
	tbl_apartment->setColumnCount(cols);

	tbl_apartment->setHorizontalHeaderLabels({ "Apartament","Proprietar","Suprafata","Tip" });

	auto row{ 0 };

	for (const auto& locatar : locatari)
	{
		const auto q_str_apart{ QString::fromStdString(to_string(locatar.getApartament())) };
		const auto q_str_owner{ QString::fromStdString(locatar.getProprietar()) };
		const auto q_str_area{ QString::fromStdString(to_string(locatar.getSuprafata())) };
		const auto q_str_type{ QString::fromStdString(locatar.getTip()) };

		const QStringList q_string_list{ q_str_apart,  q_str_owner, q_str_area, q_str_type };

		QTableWidgetItem* apart_item = new QTableWidgetItem(QString::number(locatar.getApartament()));
		apart_item->setTextAlignment(Qt::AlignHCenter);
		apart_item->setData(Qt::UserRole, QStringList(q_string_list));
		apart_item->setFlags({Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* owner_item = new QTableWidgetItem(QString::fromStdString(locatar.getProprietar()));
		owner_item->setTextAlignment(Qt::AlignHCenter);
		owner_item->setData(Qt::UserRole, QStringList(q_string_list));
		owner_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* area_item = new QTableWidgetItem(QString::number(locatar.getSuprafata()));
		area_item->setTextAlignment(Qt::AlignHCenter);
		area_item->setData(Qt::UserRole, QStringList(q_string_list));
		area_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		QTableWidgetItem* type_item = new QTableWidgetItem(QString::fromStdString(locatar.getTip()));
		type_item->setTextAlignment(Qt::AlignHCenter);
		type_item->setData(Qt::UserRole, QStringList(q_string_list));
		type_item->setFlags({ Qt::ItemIsEnabled, Qt::ItemIsSelectable });

		tbl_apartment->setItem(row, 0, apart_item);
		tbl_apartment->setItem(row, 1, owner_item);
		tbl_apartment->setItem(row, 2, area_item);
		tbl_apartment->setItem(row, 3, type_item);

		++row;
	}*/
}

void GUI::setInitialState()
{
	number_of_undo = 0;
	number_of_redo = 0;
	btn_undo->setDisabled(true);
	btn_redo->setDisabled(true);

	try {
		const auto& locatari{ srv.getAll() };

		addOwnerToList(locatari);
		addOwnerToTable(locatari);
	}
	catch (const RepoException&) {
		addOwnerToList(vector<Locatar>());
		addOwnerToTable(vector<Locatar>());
	}
}