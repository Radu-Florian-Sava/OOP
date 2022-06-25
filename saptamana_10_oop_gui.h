#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_saptamana_10_oop_gui.h"

class saptamana_10_oop_gui : public QMainWindow
{
    Q_OBJECT

public:
    saptamana_10_oop_gui(QWidget *parent = Q_NULLPTR);

private:
    Ui::saptamana_10_oop_guiClass ui;
};
