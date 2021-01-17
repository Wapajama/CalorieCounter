#include "foodrecordmanager.h"

FoodRecordManager* FoodRecordManager::m_Instance = nullptr;

FoodRecordManager::FoodRecordManager()
{
    m_Values.reserve(4096);
}

NutritionValues* FoodRecordManager::AddNewValue(FoodGUID guid, MacType prot, MacType carb, MacType fat)
{
    NutritionValues val;
    val.SetName(guid);
    val.SetProtein(prot);
    val.SetFat(fat);
    val.SetCarb(carb);
    m_Values.insert(guid, val);
    return &m_Values[guid];
}

NutritionValues* FoodRecordManager::GetValueByName(const FoodGUID& guid)
{
    if (m_Values.contains(guid))
    {
        return &m_Values[guid];
    }
    return nullptr;
}
