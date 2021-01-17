#include "dailyintakemanager.h"
#include "ui_dailyintakemanager.h"

#include <foodrecordmanager.h>

DailyIntakeManager::DailyIntakeManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DailyIntakeManager)
{
    ui->setupUi(this);
}

DailyIntakeManager::~DailyIntakeManager()
{
    delete ui;
}

void DailyIntakeManager::AddFoodInstance(FoodGUID guid)
{
    NutritionValues* food = FoodRecordManager::Instance()->GetValueByName(guid);

    ui->dailyIntakeList->insertRow(0);

    // Name, Prots, Carbs, Fats, Cals

    QTableWidgetItem* itemN = new QTableWidgetItem();
    itemN->setText(food->GUID());
    ui->dailyIntakeList->setItem(0, 0, itemN);

    QTableWidgetItem* itemP = new QTableWidgetItem();
    QString prots;
    prots.setNum(food->GetProteins());
    itemP->setText(prots);
    ui->dailyIntakeList->setItem(0, 1, itemP);

    QTableWidgetItem* itemC = new QTableWidgetItem();
    QString carbs;
    carbs.setNum(food->GetCarbs());
    itemC->setText(carbs);
    ui->dailyIntakeList->setItem(0, 2, itemC);

    QTableWidgetItem* itemF = new QTableWidgetItem();
    QString fats;
    fats.setNum(food->GetFats());
    itemF->setText(fats);
    ui->dailyIntakeList->setItem(0, 3, itemF);

    QTableWidgetItem* itemCal = new QTableWidgetItem();
    QString cals;
    cals.setNum(food->GetCalories());
    itemCal->setText(cals);
    ui->dailyIntakeList->setItem(0, 4, itemCal);
}
