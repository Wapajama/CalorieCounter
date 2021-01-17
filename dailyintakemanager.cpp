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

void DailyIntakeManager::SetFloatValue(float value, int column, int row)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    QString floatvalue;
    floatvalue.setNum(value);
    item->setText(floatvalue);
    ui->dailyIntakeList->setItem(row, column, item);
}

void SetFloatText(QLineEdit* lEdit, float val)
{
    QString sValue;
    sValue.setNum(val);
    lEdit->setText(sValue);
}

void DailyIntakeManager::CalculateMacros()
{
    float prot = 0;
    float carb = 0;
    float fats = 0;
    float cals = 0;

    for (int i = 0; i < ui->dailyIntakeList->rowCount(); i++)
    {        
        prot += ui->dailyIntakeList->item(i, PROT_IND)->text().toFloat();
        carb += ui->dailyIntakeList->item(i, CARB_IND)->text().toFloat();
        fats += ui->dailyIntakeList->item(i, FATS_IND)->text().toFloat();
        cals += ui->dailyIntakeList->item(i, CALS_IND)->text().toFloat();
    }

    SetFloatText(ui->gramsProts, prot);
    SetFloatText(ui->gramsCarbs, carb);
    SetFloatText(ui->gramsFats, fats);

    SetFloatText(ui->kCalProts, prot * PROTEIN_CALORIE );
    SetFloatText(ui->kCalCarbs, carb * CARB_CALORIE );
    SetFloatText(ui->kCalFats, fats * FAT_CALORIE );

    SetFloatText(ui->totalKcals, prot * PROTEIN_CALORIE + carb * CARB_CALORIE + fats * FAT_CALORIE);

}

void DailyIntakeManager::AddFoodInstance(FoodGUID guid)
{
    NutritionValues* food = FoodRecordManager::Instance()->GetValueByName(guid);

    ui->dailyIntakeList->insertRow(0);

    // Name, Prots, Carbs, Fats, Cals

    QTableWidgetItem* itemN = new QTableWidgetItem();
    itemN->setText(food->GUID());
    ui->dailyIntakeList->setItem(0, 0, itemN);

    SetFloatValue(food->GetProteins(), 1);
    SetFloatValue(food->GetCarbs(), 2);
    SetFloatValue(food->GetFats(), 3);
    SetFloatValue(food->GetCalories(), 4);

    CalculateMacros();
}
