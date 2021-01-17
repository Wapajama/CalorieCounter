#include "dailyintakemanager.h"
#include "ui_dailyintakemanager.h"

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

}
