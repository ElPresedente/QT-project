#ifndef HOMEINSURANCE_H
#define HOMEINSURANCE_H
#include "insurance.h"

class HomeInsurance : virtual public Insurance
{
protected:
    double homeArea;
public:
    HomeInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, double HomeArea);

    QString getInsuranceObject();

    QString getId();

    QString getAdditionalInfo();

    double getHomeArea();
};

#endif // HOMEINSURANCE_H
