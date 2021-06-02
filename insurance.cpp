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

QString Insurance::getFirstName(){
    return name;
}

QString Insurance::getLastName(){
    return surname;
}

int Insurance::getIdNumber(){
    return id;
}

double Insurance::getValueNumber(){
    return value;
}

QDate Insurance::getDate(){
    return endingDate;
}

QString Insurance::getInsuranceData(){
    return insuranceObject;
}
