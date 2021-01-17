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

    QFile file("C:\\Users\\Kristoffer\\Documents\\n+++\\FoodTypes.xml");

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTreeWidgetItem* allFoodTypes = new QTreeWidgetItem(ui->foodTypeCategories);
    QTreeWidgetItem* allFoodTypesChild = new QTreeWidgetItem(allFoodTypes);
    allFoodTypes->setText(0, "All Food Types");
    ui->foodTypeCategories->addTopLevelItem(allFoodTypes);
    allFoodTypes->addChild(allFoodTypesChild);

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
            NutritionValues* val = FoodRecordManager::Instance()->AddNewValue(
                reader.attributes().value("name").toString(),
                reader.attributes().value("protein").toFloat(),
                reader.attributes().value("carbs").toFloat(),
                reader.attributes().value("fat").toFloat());

            FoodData* test = new FoodData(val);
            test->SetName(val->Name());

            QString valTextp;
            QString valTextc;
            QString valTextf;

            valTextp.setNum(val->GetProteins());
            valTextc.setNum(val->GetCarbs());
            valTextf.setNum(val->GetFats());

            test->ui->lineEdit_prots->setText(valTextp);
            test->ui->lineEdit_carbs->setText(valTextc);
            test->ui->lineEdit_fats->setText(valTextf);

            QListWidgetItem* testItem = new QListWidgetItem();

            testItem->setSizeHint(test->minimumSizeHint());
            ui->foodTypesList->addItem(testItem);
            ui->foodTypesList->setItemWidget(testItem, test);
        }
    }

    //pModel.setSourceModel(&m_Model);
    //m_SModel = ui->foodTypesList->selectionModel();
    //m_SModel->setModel(&pModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

