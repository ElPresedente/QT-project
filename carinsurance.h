#ifndef CARINSURANCE_H
#define CARINSURANCE_H
#include "insurance.h"

class CarInsurance : virtual public Insurance
{
public:
    CarInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, int CarVIN);

    int carVIN;

    QString getInsuranceObject();

    QString getId();

    //QString getCarVIN();

    QString getAdditionalInfo();
};

#endif // CARINSURANCE_H
