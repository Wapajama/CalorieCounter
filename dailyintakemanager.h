#ifndef DAILYINTAKEMANAGER_H
#define DAILYINTAKEMANAGER_H

#include <QWidget>
#include <FoodDataTypes.h>

#define NAME_IND 0

#define PROT_IND 1
#define CARB_IND 2
#define FATS_IND 3

#define CALS_IND 4

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

private:
    Ui::DailyIntakeManager *ui;

    void SetFloatValue(float value, int column, int row = 0);
    void CalculateMacros();
};

#endif // DAILYINTAKEMANAGER_H
