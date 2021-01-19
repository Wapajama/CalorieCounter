#include "dailyintakemanager.h"
#include "ui_dailyintakemanager.h"
#include <QXmlStreamWriter>
#include <QDateTime>
#include <foodrecordmanager.h>
#include <QFile>

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

void DailyIntakeManager::SetStringValue(QString value, int column, int row)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    item->setText(value);
    ui->dailyIntakeList->setItem(row, column, item);
}

void DailyIntakeManager::SetFloatValue(float value, int column, int row)
{
    QTableWidgetItem* item = new QTableWidgetItem();
    QString floatvalue;
    floatvalue.setNum(value);
    item->setText(floatvalue);
    ui->dailyIntakeList->setItem(row, column, item);
}

float GetFloatFromAtt(const QString& name, const QXmlStreamAttributes& attrs)
{
    for (int i = 0; i < attrs.count(); i++)
    {
        if (attrs[i].name() == name)
        {
            return attrs[i].value().toFloat();
        }
    }
    return 0.0f;
}

QString GetStringFromAtt(const QString& name, const QXmlStreamAttributes& attrs)
{
    for (int i = 0; i < attrs.count(); i++)
    {
        if (attrs[i].name() == name)
        {
            return attrs[i].value().toString();
        }
    }
    return "";
}

QTableWidgetItem* DailyIntakeManager::GetTableItem(int id, int row)
{
    return ui->dailyIntakeList->item(row, id);
}

void DailyIntakeManager::PopulateList()
{
    QFile file(GetTodaysFileName());

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
        ui->dailyIntakeList->insertRow(0);

        QXmlStreamAttributes attrs = reader.attributes();
        // GetTableItem(GRAM_IND)->setText(GetStringFromAtt(GRAM_TXT, attrs));
        // GetTableItem(NAME_IND)->setText(GetStringFromAtt(NAME_TXT, attrs));
        // GetTableItem(PROT_IND)->setText(GetStringFromAtt(PROT_TXT, attrs));
        // GetTableItem(CARB_IND)->setText(GetStringFromAtt(CARB_TXT, attrs));
        // GetTableItem(FATS_IND)->setText(GetStringFromAtt(FATS_TXT, attrs));
        // GetTableItem(CALS_IND)->setText(GetStringFromAtt(CALS_TXT, attrs));
        SetStringValue(GetStringFromAtt(GRAM_TXT, attrs), GRAM_IND);
        SetStringValue(GetStringFromAtt(NAME_TXT, attrs), NAME_IND);
        SetStringValue(GetStringFromAtt(PROT_TXT, attrs), PROT_IND);
        SetStringValue(GetStringFromAtt(CARB_TXT, attrs), CARB_IND);
        SetStringValue(GetStringFromAtt(FATS_TXT, attrs), FATS_IND);
        SetStringValue(GetStringFromAtt(CALS_TXT, attrs), CALS_IND);
    }
    file.close();
}

void SetFloatText(QLineEdit* lEdit, float val)
{
    QString sValue;
    sValue.setNum(val);
    lEdit->setText(sValue);
}

QString DailyIntakeManager::GetTodaysFileName()
{
    QDateTime now = QDateTime::currentDateTime();
    return "C:\\Users\\Kristoffer\\Documents\\Qt Projects\\Data\\" + QString("DailyIntake " + now.date().toString() + ".xml");
}

void DailyIntakeManager::WriteToFile()
{
    QString fileOfToday = GetTodaysFileName();

    QXmlStreamWriter writer;
    QFile file;
    file.setFileName(fileOfToday);
    writer.setDevice(&file);
    bool result = file.open(QFile::Text | QFile::WriteOnly);

    writer.setAutoFormatting(true);

    writer.writeStartDocument();
    writer.writeStartElement("Foods");

    for (int i = 0; i < ui->dailyIntakeList->rowCount(); i++)
    {
        writer.writeStartElement("Food");

        writer.writeAttribute(GRAM_TXT, ui->dailyIntakeList->item(i, GRAM_IND)->text());
        writer.writeAttribute(NAME_TXT, ui->dailyIntakeList->item(i, NAME_IND)->text());
        writer.writeAttribute(PROT_TXT, ui->dailyIntakeList->item(i, PROT_IND)->text());
        writer.writeAttribute(CARB_TXT, ui->dailyIntakeList->item(i, CARB_IND)->text());
        writer.writeAttribute(FATS_TXT, ui->dailyIntakeList->item(i, FATS_IND)->text());
        writer.writeAttribute(CALS_TXT, ui->dailyIntakeList->item(i, CALS_IND)->text());

        writer.writeEndElement();
    }
    writer.writeEndDocument();
    file.flush();
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
    ui->dailyIntakeList->setItem(0, NAME_IND, itemN);

    SetFloatValue(50, GRAM_IND);
    SetFloatValue(food->GetProteins(), PROT_IND);
    SetFloatValue(food->GetCarbs(), CARB_IND);
    SetFloatValue(food->GetFats(), FATS_IND);
    SetFloatValue(food->GetCalories(), CALS_IND);

    CalculateMacros();
    WriteToFile();
}
