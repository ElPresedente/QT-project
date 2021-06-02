#ifndef HEALTHINSURANCE_H
#define HEALTHINSURANCE_H
#include "insurance.h"

class HealthInsurance : virtual public Insurance
{
protected:
    QString insuranceCity;
public:
    HealthInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceCity);

    QString getInsuranceObject();

    QString getId();

    QString getAdditionalInfo();

    QString getInsuranceCity();
};

#endif // HEALTHINSURANCE_H
