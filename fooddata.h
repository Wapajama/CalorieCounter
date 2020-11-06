#ifndef FOODDATA_H
#define FOODDATA_H

#include <QFrame>
#include <FoodDataTypes.h>

namespace Ui {
class FoodData;
}

class FoodData : public QWidget
{
    Q_OBJECT

public:
    explicit FoodData(QWidget *parent = nullptr);
    ~FoodData();

    inline NutritionValues& Values(){return m_Values;}


    void SetName(const QString& name);
    Ui::FoodData *ui;

private:
    NutritionValues m_Values;
};

#endif // FOODDATA_H
