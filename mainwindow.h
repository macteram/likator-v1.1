#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QFileDialog>
#include "humaninfo.h"

#include <QSerialPort>
#include <QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QSqlDatabase database;
    QSqlQuery query;
    QString openDB;
    QString selectedUID;
    bool DBOPEN = false;    //для проверки открылась база данных или нет
    int SIZE = 7;           //размер массива в котром хранятся данные о выбранном человеке
    HumanInfo info;

public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void readData();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    //инициализация компорта
       QSerialPort *likatorrfid;
       static const quint16 likatorrfid_uno_vendor_id = 9025;
       static const quint16 likatorrfid_uno_product_id = 67;
       QString likatorrfid_port_name;
      bool likatorrfid_is_available;

      //инициализация компорта
};

#endif // MAINWINDOW_H
