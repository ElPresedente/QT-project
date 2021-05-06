#ifndef HEALTHINSURANCE_H
#define HEALTHINSURANCE_H
#include "insurance.h"

class HealthInsurance : virtual public Insurance
{
public:
    HealthInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceCity);

    QString insuranceCity;

    QString getInsuranceObject();

    QString getId();

    QString getAdditionalInfo();
};

#endif // HEALTHINSURANCE_H
