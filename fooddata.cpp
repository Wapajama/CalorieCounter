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

void FoodData::SetName(const FoodGUID& guid)
{
    m_Values->SetGUID(guid);
    ui->foodTypeName->setText(guid);
}

FoodData::~FoodData()
{
    delete ui;
 }

void FoodData::on_pushButton_Bg_clicked()
{
    emit AddFoodButtonClicked(m_Values->GUID());
}
