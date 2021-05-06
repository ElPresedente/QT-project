#include "carinsurance.h"

CarInsurance::CarInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, int CarVIN) :
    Insurance(Name, Surname, Id, Value, EndingDate, InsuranceObj),
    carVIN(CarVIN)
{};

QString CarInsurance::getId()
{
    return QString("C_"+QString::number(id));
}

QString CarInsurance::getInsuranceObject()
{
    return QString("Car num:\n"+insuranceObject);
}

QString CarInsurance::getAdditionalInfo()
{
    return QString("VIN number:\n"+QString::number(carVIN));
}

