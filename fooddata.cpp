#include "fooddata.h"
#include "ui_fooddata.h"

FoodData::FoodData(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FoodData)
{
    ui->setupUi(this);
}

void FoodData::SetName(const QString& name)
{
    m_Values.SetName((name));
    ui->foodTypeName->setText(name);
}

FoodData::~FoodData()
{
    delete ui;
}
