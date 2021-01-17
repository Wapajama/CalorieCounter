#pragma once

#include <QString>

typedef float MacronutrientType;
typedef float MicronutrientType;
typedef float KCalorieType;

typedef MacronutrientType MacType;
typedef MicronutrientType MicType;
typedef KCalorieType KCType;

typedef QString FoodGUID;

#define FAT_CALORIE 9.0f
#define CARB_CALORIE 4.0f
#define PROTEIN_CALORIE 4.0f

#include <QString>
#include <QObject>
class NutritionValues
{
public:
    NutritionValues ()
        :m_Fat(0),
        m_Carb(0),
        m_Protein(0),
        m_Calories(0)
    {}

    NutritionValues(const NutritionValues& other)
    {
        this->m_Name = other.m_Name;

        this->m_Fat = other.m_Fat;
        this->m_Carb = other.m_Carb;
        this->m_Protein = other.m_Protein;

        this->m_Calories = other.m_Calories;
    }


    inline void SetFat(MacType fat){m_Fat = fat; CalculateKalories();}
    inline void SetCarb(MacType carb){m_Carb = carb; CalculateKalories();}
    inline void SetProtein(MacType protein){m_Protein = protein; CalculateKalories();}

    inline MacType GetFats()const{return m_Fat;}
    inline MacType GetCarbs()const{return m_Carb;}
    inline MacType GetProteins()const{return m_Protein;}
    inline KCalorieType GetCalories(){return m_Calories;}

    inline QString Name(){return m_Name;}
    inline void SetName(const QString& name){m_Name = name;}

private:

    void CalculateKalories()
    {
        m_Calories = (m_Fat * FAT_CALORIE + m_Carb * CARB_CALORIE + m_Protein * PROTEIN_CALORIE);
    }

    QString m_Name;

    MacType m_Fat;
    MacType m_Carb;
    MacType m_Protein;

    KCType  m_Calories;
};
