#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    table = ui->tableWidget;
    table->setColumnWidth(4, 200);
    table->setColumnWidth(5, 200);

    currentStatus = widgetStatus::hide;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawTable()
{
    table->setRowCount(data.length());
    for(int i = 0; i < data.length(); i++){
        setTableItem(data.at(i), i);
    }
}
void MainWindow::setTableItem(Insurance* ptr, int rowNum)
{
    QTableWidgetItem* item;
    item = new QTableWidgetItem(ptr->getId());
    table->setItem(rowNum, 0, item);

    item = new QTableWidgetItem(ptr->getName());
    table->setItem(rowNum, 1, item);

    item = new QTableWidgetItem(ptr->getValue());
    table->setItem(rowNum, 2, item);

    item = new QTableWidgetItem(ptr->getEndingDate());
    table->setItem(rowNum, 3, item);

    item = new QTableWidgetItem(ptr->getInsuranceObject());
    table->setItem(rowNum, 4, item);

    item = new QTableWidgetItem(ptr->getAdditionalInfo());
    table->setItem(rowNum, 5, item);

    table->setRowHeight(rowNum, 75);
}

void MainWindow::changeWidget(widgetStatus status){
    if(currentStatus == status){
        return;
    }
    switch(status){
        case widgetStatus::hide:{
            if(widgetLayout == nullptr)
                return;
            for(int i = widgetLayout->count()-1; i >= 0; i-- ){
                delete widgetLayout->itemAt(i)->widget();
                delete widgetLayout->itemAt(i);
            }
            delete widgetLayout->widget();
            delete widgetLayout;
            break;
        }
        case widgetStatus::add:{
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QPushButton* carbutton = new QPushButton("Car insurance");
            connect(carbutton, SIGNAL(clicked()), this, SLOT(on_carInsuranceButton_clicked()));

            QPushButton* healthbutton = new QPushButton("Health insurance");
            connect(healthbutton, SIGNAL(clicked()), this, SLOT(on_healthInsuranceButton_clicked()));

            QPushButton* homebutton = new QPushButton("Home insurance");
            connect(homebutton, SIGNAL(clicked()), this, SLOT(on_homeInsuranceButton_clicked()));

            widgetLayout->addWidget(carbutton, 0, 0);
            widgetLayout->addWidget(healthbutton, 1, 0);
            widgetLayout->addWidget(homebutton, 2, 0);
            break;
        }
        case widgetStatus::addCar:{//CarInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, int CarVIN);
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QLabel* idLabel = new QLabel("Insuranse's id:");
            QLineEdit* idEdit = new QLineEdit();
            widgetLayout->addWidget(idLabel, 0, 0);
            widgetLayout->addWidget(idEdit, 0, 1);

            QLabel* nameLabel = new QLabel("Insuranse's owner name:");
            QLineEdit* nameEdit = new QLineEdit();
            widgetLayout->addWidget(nameLabel, 1, 0);
            widgetLayout->addWidget(nameEdit, 1, 1);

            QLabel* surnameLabel = new QLabel("Insurance's owner surname:");
            QLineEdit* surnameEdit = new QLineEdit();
            widgetLayout->addWidget(surnameLabel, 2, 0);
            widgetLayout->addWidget(surnameEdit, 2, 1);

            QLabel* valueLabel = new QLabel("Insurance's value:");
            QLineEdit* valueEdit = new QLineEdit();
            valueEdit->setValidator(new QDoubleValidator(0, 999999, 3));
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("Insurance starting date:");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 4, 0);
            widgetLayout->addWidget(dateEdit, 4, 1);

            QLabel* insObjLabel = new QLabel("Car number:");
            QLineEdit* insObjEdit = new QLineEdit();
            widgetLayout->addWidget(insObjLabel, 5, 0);
            widgetLayout->addWidget(insObjEdit, 5, 1);

            QLabel* carVINLabel = new QLabel("Car VIN number:");
            QLineEdit* carVINEdit = new QLineEdit();
            widgetLayout->addWidget(carVINLabel, 6, 0);
            widgetLayout->addWidget(carVINEdit, 6, 1);

            QPushButton* submitButton = new QPushButton("Submit");
            widgetLayout->addWidget(submitButton, 7, 0);
            break;
        }
        case widgetStatus::addHealth:{//HealthInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceCity);
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            break;
        }
        case widgetStatus::addHome:{//HomeInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, double HomeArea);
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);
            break;
        }
    }
    currentStatus = status;
}

void MainWindow::on_pushButton_clicked()
{
    Insurance *newdata = new CarInsurance(1, "nameee", "Surnamee", 150.3, QDate(2000, 10, 17), "test", 1204439232);
    data.append(newdata);
    drawTable();
}

void MainWindow::on_pushButton_2_clicked()
{
    Insurance *newdata = new HealthInsurance(2, "Name", "Surname", 54.125, QDate(2002, 10, 17), "Orel");
    data.append(newdata);
    drawTable();
}

void MainWindow::on_pushButton_3_clicked()
{
    Insurance *newdata = new HomeInsurance(3, "Вовка", "Коробка", 150.3, QDate(2006, 11, 7), "хуй знает чо писать", 250.5);
    data.append(newdata);
    drawTable();
}

void MainWindow::test(int i){
    qDebug()<<i;
}

void MainWindow::on_addButton_clicked()
{
    changeWidget(widgetStatus::add);
}

void MainWindow::on_removeButton_clicked()
{
    changeWidget(widgetStatus::hide);
}

void MainWindow::on_carInsuranceButton_clicked(){
    qDebug()<<"car insurance clicked";
    changeWidget(widgetStatus::addCar);
}

void MainWindow::on_healthInsuranceButton_clicked(){
    qDebug()<<"health insurance clicked";
    changeWidget(widgetStatus::addHealth);
}

void MainWindow::on_homeInsuranceButton_clicked(){
    qDebug()<<"home insurance clicked";
    changeWidget(widgetStatus::addHome);
}
