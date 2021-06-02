#ifndef CARINSURANCE_H
#define CARINSURANCE_H
#include "insurance.h"

class CarInsurance : virtual public Insurance
{
protected:
    long long carVIN;
public:
    CarInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, long long CarVIN);

    QString getInsuranceObject();

    QString getId();

    long long getCarVIN();

    QString getAdditionalInfo();
};

#endif // CARINSURANCE_H
