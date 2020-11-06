#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#include <fooddata.h>
#include "ui_fooddata.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    QFile file("C:\\Users\\Kristoffer\\Documents\\n+++\\FoodTypes.xml");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QXmlStreamReader reader(&file);
    while(!reader.atEnd())
    {
        if (!reader.readNextStartElement())
        {
            continue;
        }
        QString value = reader.name().toString();
        if (reader.name() == "FoodType")
        {
            FoodData* test = new FoodData();
            test->SetName(reader.attributes().value("name").toString());
            test->ui->lineEdit_carbs->setText(reader.attributes().value("carbs").toString());
            test->ui->lineEdit_fats->setText(reader.attributes().value("fat").toString());
            test->ui->lineEdit_prots->setText(reader.attributes().value("protein").toString());

            QListWidgetItem* testItem = new QListWidgetItem(ui->FoodTypesList);
            testItem->setSizeHint(test->minimumSizeHint());
            //ui->FoodTypesList->addItem(testItem);
            ui->FoodTypesList->setItemWidget(testItem, test);
        }
    }

    //    FoodData* test = new FoodData();
    //    FoodData* test2 = new FoodData(ui->FoodTypesList->viewport());
    //    QListWidgetItem* testItem = new QListWidgetItem(ui->FoodTypesList);
    //    QListWidgetItem* testItem2 = new QListWidgetItem(ui->FoodTypesList);
    //    testItem->setSizeHint(test->minimumSizeHint());
    //    testItem2->setSizeHint(test2->minimumSizeHint());
    //    ui->FoodTypesList->addItem(testItem);
    //    ui->FoodTypesList->addItem(testItem2);
    //    ui->FoodTypesList->setItemWidget(testItem, test);
    //    ui->FoodTypesList->setItemWidget(testItem2, test2);
    // ui->FoodTypesList->addScrollBarWidget(test, Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

