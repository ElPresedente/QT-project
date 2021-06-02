#ifndef INSURANCE_H
#define INSURANCE_H
#include <QString>
#include <QDate>

class Insurance
{
protected:
    QString name;
    QString surname;
    int id;
    double value; //максимальный размер компенсации
    QDate endingDate;
    QString insuranceObject; //номер машины/адрес дома/здоровье
public:
    virtual ~Insurance();



    QString getName();
    QString getValue();
    QString getEndingDate();

    QString getFirstName();
    QString getLastName();
    int getIdNumber();
    double getValueNumber();
    QDate getDate();
    QString getInsuranceData();

    virtual QString getId() = 0;

    virtual QString getInsuranceObject() = 0;

    virtual QString getAdditionalInfo() = 0;
protected:
    Insurance(QString Name, QString Surname, int Id, double Value, QDate EndingDate, QString insuranceObj);
};

#endif // INSURANCE_H
