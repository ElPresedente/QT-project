#include "insurance.h"


Insurance::Insurance(QString Name, QString Surname, int Id, double Value, QDate EndingDate, QString insuranceObj) :
    name(Name), surname(Surname), id(Id), value(Value),
    endingDate(EndingDate), insuranceObject(insuranceObj)
{};

QString Insurance::getName()
{
    return QString(name + " " + surname);
}

QString Insurance::getValue()
{
    return QString::number(value);
}

QString Insurance::getEndingDate()
{
    return endingDate.toString();
}

Insurance::~Insurance(){

}
