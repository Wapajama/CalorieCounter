#ifndef DAILYINTAKEMANAGER_H
#define DAILYINTAKEMANAGER_H

#include <QWidget>
#include <FoodDataTypes.h>

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
};

#endif // DAILYINTAKEMANAGER_H
