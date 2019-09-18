#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Create a data model for the mapping table from a CSV file
    csvModel = new QStandardItemModel(this);
    csvModel->setColumnCount(5);
    csvModel->setHorizontalHeaderLabels(QStringList()<< "CAR" << "POS" << "PIC" << "LAP" << "Time");
    ui->tableView->setModel(csvModel);

    //Open the file from the resources. Instead of the file
    //Need to specify the path to your desired file
    QFile file(":/new/prefix1/csvFiles/23_Time Cards_Race.CSV");
    if ( !file.open(QFile::ReadOnly | QFile::Text)){
        qDebug() << "File not exists";
    } else {
        //Create thread to retrieve data from a file
        QTextStream in(&file);
        //Reads the data up tp the end of file
        while (!in.atEnd())
        {
            QString line = in.readLine();
            //Adding to the model in line with elements
            QList<QStandardItem *> standardItemList;
            //Consider that the lines separated by semicolons into colums
            for (QString item : line.split(";")){
                standardItemList.append(new QStandardItem(item));
            }
            csvModel->insertRow(csvModel->rowCount(), standardItemList);
        }
        file.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete csvModel;
}

