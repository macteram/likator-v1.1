#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "humaninfo.h"
#include "ui_humaninfo.h"
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    // инициализирую порт и проверяю информацию об устройстве считывания
    ui->setupUi(this);

    likatorrfid_is_available = false;
    likatorrfid_port_name = "";
    likatorrfid = new QSerialPort;
    QString read_id = "";

    qDebug() << "Number of available ports: " << QSerialPortInfo::availablePorts().length();
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
         {
        qDebug() << "Has vendor ID: " << serialPortInfo.hasVendorIdentifier();
        if(serialPortInfo.hasVendorIdentifier()){
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier();
                                                }
        qDebug() << "Has Product ID: " << serialPortInfo.hasProductIdentifier();
        if(serialPortInfo.hasProductIdentifier())  {
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier();
                                                   }
         }

    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts())
   {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier())
      {
            if(serialPortInfo.vendorIdentifier() == likatorrfid_uno_vendor_id)
            {
                if(serialPortInfo.productIdentifier() == likatorrfid_uno_product_id)
                {
                    likatorrfid_port_name = serialPortInfo.portName();
                    likatorrfid_is_available = true;
                }
            }
      }
   }
 // инициализирую порт и проверяю информацию об устройстве считывания

    //открываю работу с портом если все ок
    if(likatorrfid_is_available)
   {
    // open and configure the serialport
    likatorrfid->setPortName(likatorrfid_port_name);
   // likatorrfid->open(QSerialPort::WriteOnly);
    likatorrfid->open(QSerialPort::ReadOnly);
    likatorrfid->setBaudRate(QSerialPort::Baud9600);
    likatorrfid->setDataBits(QSerialPort::Data8);
    likatorrfid->setParity(QSerialPort::NoParity);
    likatorrfid->setStopBits(QSerialPort::OneStop);
    likatorrfid->setFlowControl(QSerialPort::NoFlowControl);
    ui->statusBar->showMessage("Установлено соединение с модулем дисконта");

   }else
   {
    ui->statusBar->showMessage("Нет соединения с модулем дисконта");


   }

        connect(likatorrfid, &QSerialPort::readyRead, this, &MainWindow::readData);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    openDB = QFileDialog::getOpenFileName(this, "Open file", "", "Database (*sqlite)"); //указываем путь на базу данных
    database = QSqlDatabase::addDatabase("QSQLITE");    //указываем тип СУБД базы данных
    database.setDatabaseName(openDB);                   //передаем в объект выбранную базу данных

    if(database.open())
    {
        //qDebug()<<"DataBase is open";
        query = QSqlQuery(database);
        DBOPEN = true;
         ui->statusBar->showMessage("База данных загружена");

    }
    else
    {
        //qDebug()<<database.lastError().text();
        DBOPEN = false;

    }
}



void MainWindow::on_pushButton_2_clicked()
{
    if(DBOPEN)
    {
        selectedUID = ui->UID->text();              //запись в переменную набранного пользователем значения UID

        query.exec("SELECT * FROM tablename1");     //запрос в базу данных

        while (query.next())
        {
            QString value = query.value(0).toString();          //поиск по UID
            if(selectedUID==value)
            {
                //qDebug()<<"UID = "<<selectedUID<<" = "<<value;

                QString *humaninfo = new QString[SIZE];     //определяем массив для хранения данных о выбранном человеке

                for (int i =0;i<SIZE;i++)
                    humaninfo[i] = query.value(i).toString();

                info.setText(humaninfo);    //сеттер
                info.setModal(true);
                info.exec();

                delete [] humaninfo;
            }
        }
    }
}

void MainWindow::readData()
{
    const QByteArray data = likatorrfid->readAll();

    ui->plainTextEdit->insertPlainText(data);
    ui->UID->insert(data);

    if (ui->UID->text().back()== '\n') {
        QString str = ui->UID->text();
        ui->UID->clear();
        str.remove(8,2);
        ui->lineEdit->setText(str);
        if(DBOPEN)
            {
             selectedUID = str;             //запись в переменную набранного пользователем значения UID
             query.exec("SELECT * FROM tablename1");     //запрос в базу данных
             while (query.next())
                 {
                  QString value = query.value(0).toString();          //поиск по UID
                  if(selectedUID==value)
                      {
                      QString *humaninfo = new QString[SIZE];     //определяем массив для хранения данных о выбранном человеке
                      for (int i =0;i<SIZE;i++)
                          humaninfo[i] = query.value(i).toString();
                      info.setText(humaninfo);    //сеттер
                      info.setModal(true);
                      info.exec();
                      delete [] humaninfo;
            }
        }
    }
        ui->UID->clear();
    }

}


void MainWindow::on_pushButton_3_clicked()
{
     ui->UID->clear();
}
