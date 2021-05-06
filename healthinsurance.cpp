#include "healthinsurance.h"

HealthInsurance::HealthInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceCity):
    Insurance(Name, Surname, Id, Value, EndingDate, "Health"),
    insuranceCity(InsuranceCity)
{};
QString HealthInsurance::getId()
{
    return QString("H_"+QString::number(id));
}

QString HealthInsurance::getInsuranceObject()
{
    return insuranceObject;
}

QString HealthInsurance::getAdditionalInfo()
{
    return QString("Insurance city:\n"+insuranceCity);
}
