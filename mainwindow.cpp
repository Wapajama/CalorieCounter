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
    QTreeWidgetItem* allFoodTypes = new QTreeWidgetItem(ui->foodTypeCategories);
    QTreeWidgetItem* allFoodTypesChild = new QTreeWidgetItem(allFoodTypes);
    // QListWidget* newFoodTypesList = new QListWidget();
    allFoodTypes->setText(0, "All Food Types");
    ui->foodTypeCategories->addTopLevelItem(allFoodTypes);
    allFoodTypes->addChild(allFoodTypesChild);
    // ui->foodTypeCategories->setItemWidget(allFoodTypesChild, 0, ui->foodTypesList);

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

            QStandardItem* testItemModelIndex = new QStandardItem(test->ui->foodTypeName->text());
            m_Model.appendRow(testItemModelIndex);
            // QModelIndex testIndex = testItemModelIndex->index(newFoodTypesList);
            QListWidgetItem* testItem = new QListWidgetItem();
            //QListWidgetItem* testItem = reinterpret_cast<QListWidgetItem*>((ui->foodTypesList->indexWidget(testItemModelIndex->index())));

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

