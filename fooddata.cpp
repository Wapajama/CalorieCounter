#include "fooddata.h"
#include "ui_fooddata.h"

FoodData::FoodData(NutritionValues* data,
                   QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FoodData),
    m_Values(data)
{
    ui->setupUi(this);
}

void FoodData::SetName(const QString& name)
{
    m_Values->SetName((name));
    ui->foodTypeName->setText(name);
}

FoodData::~FoodData()
{
    delete ui;
}

void FoodData::on_pushButton_Bg_clicked()
{
    emit AddFoodButtonClicked(m_Values);
}
