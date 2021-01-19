#ifndef DAILYINTAKEMANAGER_H
#define DAILYINTAKEMANAGER_H

#include <QWidget>
#include <FoodDataTypes.h>

#define GRAM_IND 0
#define NAME_IND 1
#define PROT_IND 2
#define CARB_IND 3
#define FATS_IND 4
#define CALS_IND 5

#define GRAM_TXT "gram"
#define NAME_TXT "name"
#define PROT_TXT "prot"
#define CARB_TXT "carb"
#define FATS_TXT "fats"
#define CALS_TXT "cals"

namespace Ui {
class DailyIntakeManager;
}

class DailyIntakeManager : public QWidget
{
    Q_OBJECT

public:
    explicit DailyIntakeManager(QWidget *parent = nullptr);
    ~DailyIntakeManager();

public slots:
    void AddFoodInstance(FoodGUID guid);

    void PopulateList();
private:
    Ui::DailyIntakeManager *ui;

    void WriteToFile();
    class QTableWidgetItem* GetTableItem(int id, int row = 0);
    QString GetTodaysFileName();

    void SetFloatValue(float value, int column, int row = 0);
    void SetStringValue(QString value, int column, int row = 0);
    void CalculateMacros();
};

#endif // DAILYINTAKEMANAGER_H
