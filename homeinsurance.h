#ifndef HOMEINSURANCE_H
#define HOMEINSURANCE_H
#include "insurance.h"

class HomeInsurance : virtual public Insurance
{
public:
    HomeInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, double HomeArea);

    double homeArea;

    QString getInsuranceObject();

    QString getId();

    QString getAdditionalInfo();
};

#endif // HOMEINSURANCE_H
