#ifndef FOODRECORDMANAGER_H
#define FOODRECORDMANAGER_H
#include <QHash>
#include <FoodDataTypes.h>

class FoodRecordManager
{
private:

    static FoodRecordManager* m_Instance;

    FoodRecordManager();

public:

    static void Create()
    {
        if (m_Instance == nullptr)
        {
            m_Instance = new FoodRecordManager();
        }
    }

    static FoodRecordManager* Instance() {return m_Instance;}
    NutritionValues* AddNewValue(FoodGUID guid, MacType prot, MacType carb, MacType fat);
    NutritionValues* GetValueByName(const FoodGUID& guid);

private:
    QHash<FoodGUID, NutritionValues> m_Values;

};

#endif // FOODRECORDMANAGER_H
