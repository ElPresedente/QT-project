#include "homeinsurance.h"


HomeInsurance::HomeInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, double HomeArea):
    Insurance(Name, Surname, Id, Value, EndingDate, InsuranceObj),
    homeArea(HomeArea)
{}

QString HomeInsurance::getId()
{
    return QString("B_"+QString::number(id));
}

QString HomeInsurance::getInsuranceObject()
{
    return QString("House at:\n" + insuranceObject);
}

QString HomeInsurance::getAdditionalInfo()
{
    return QString("House area: "+QString::number(homeArea));
}