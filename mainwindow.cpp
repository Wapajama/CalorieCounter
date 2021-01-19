#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QXmlStreamReader>
#include <fooddata.h>
#include "ui_fooddata.h"
#include <QFile>
#include <foodrecordmanager.h>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    FoodRecordManager::Create();

    QFile file("C:\\Users\\Kristoffer\\Documents\\Qt Projects\\Data\\FoodTypes.xml");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }

    QXmlStreamReader reader(&file);

    ui->dailyIntake->PopulateList();

    while(!reader.atEnd())
    {
        if (!reader.readNextStartElement())
        {
            continue;
        }
        QString value = reader.name().toString();
        if (reader.name() == "FoodType")
        {
            NutritionValues* val = FoodRecordManager::Instance()->AddNewValue(
                reader.attributes().value("name").toString(),
                reader.attributes().value("protein").toFloat(),
                reader.attributes().value("carbs").toFloat(),
                reader.attributes().value("fat").toFloat());

            FoodData* test = new FoodData(val);
            test->SetName(val->GUID());

            QString valTextp;
            QString valTextc;
            QString valTextf;

            valTextp.setNum(val->GetProteins());
            valTextc.setNum(val->GetCarbs());
            valTextf.setNum(val->GetFats());

            test->ui->lineEdit_prots->setText(valTextp);
            test->ui->lineEdit_carbs->setText(valTextc);
            test->ui->lineEdit_fats->setText(valTextf);

            connect(test, SIGNAL(AddFoodButtonClicked(FoodGUID)), this->ui->dailyIntake, SLOT(AddFoodInstance(FoodGUID)));

            QListWidgetItem* testItem = new QListWidgetItem();

            testItem->setSizeHint(test->minimumSizeHint());
            ui->foodTypesList->addItem(testItem);
            ui->foodTypesList->setItemWidget(testItem, test);
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

