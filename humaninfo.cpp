#include "humaninfo.h"
#include "ui_humaninfo.h"
#include "mainwindow.h"

HumanInfo::HumanInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HumanInfo)
{
    ui->setupUi(this);
}

void HumanInfo::setText(QString *array)     //вывод в Line Edit второго окна данных о человеке
{
    ui->uid->setText(array[0]);
    ui->name1->setText(array[1]);
    ui->name2->setText(array[2]);
    ui->name3->setText(array[3]);
    ui->adress->setText(array[4]);
    ui->birthday->setText(array[5]);
    ui->cardname->setText(array[6]);

}

HumanInfo::~HumanInfo()
{
    delete ui;
}





