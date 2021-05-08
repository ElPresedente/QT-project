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

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    currentStatus = widgetStatus::hide;
    locale = new QLocale();
    tableData = nullptr;

    setEditMode(false);
}

MainWindow::~MainWindow()
{
    changeWidget(widgetStatus::hide);
    delete ui;
    delete tableData;
    delete locale;
}

void MainWindow::drawTable()
{
    if(tableData == nullptr){
        table->setRowCount(data.length());
        for(int i = 0; i < data.length(); i++){
            setTableItem(data.at(i), i);
        }
    }
    else{
        table->setRowCount(tableData->length());
        for(int i = 0; i < tableData->length(); i++){
            setTableItem(data.at(tableData->at(i)), i);
        }
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
            connect(carbutton, SIGNAL(clicked()),
                    this, SLOT(on_carInsuranceButton_clicked()));

            QPushButton* healthbutton = new QPushButton("Health insurance");
            connect(healthbutton, SIGNAL(clicked()),
                    this, SLOT(on_healthInsuranceButton_clicked()));

            QPushButton* homebutton = new QPushButton("Home insurance");
            connect(homebutton, SIGNAL(clicked()),
                    this, SLOT(on_homeInsuranceButton_clicked()));

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
            QDoubleValidator* validator = new QDoubleValidator(0, 999999, 2);
            valueEdit->setValidator(validator);
            qDebug()<<validator->locale();
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("Insurance ending date:");
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
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitCarButton_clicked()));
            break;
        }
        case widgetStatus::addHealth:{//HealthInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceCity);
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QLabel* idLabel = new QLabel("Insuranse's id:");
            QLineEdit* idEdit = new QLineEdit();
            idEdit->setValidator(new QIntValidator(0, 99999));
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
            valueEdit->setValidator(new QDoubleValidator(0, 999999, 2));
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("Insurance ending date:");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 4, 0);
            widgetLayout->addWidget(dateEdit, 4, 1);
            qDebug()<<dateEdit->date().isNull();

            QLabel* insCityLabel = new QLabel("City:");
            QLineEdit* insCityEdit = new QLineEdit();
            widgetLayout->addWidget(insCityLabel, 5, 0);
            widgetLayout->addWidget(insCityEdit, 5, 1);

            QPushButton* submitButton = new QPushButton("Submit");
            widgetLayout->addWidget(submitButton, 7, 0);
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitHealthButton_clicked()));
            break;
        }
        case widgetStatus::addHome:{//HomeInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, double HomeArea);
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
            valueEdit->setValidator(new QDoubleValidator(0, 999999, 2));
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("Insurance ending date:");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 4, 0);
            widgetLayout->addWidget(dateEdit, 4, 1);

            QLabel* insObjLabel = new QLabel("House adress:");
            QLineEdit* insObjEdit = new QLineEdit();
            widgetLayout->addWidget(insObjLabel, 5, 0);
            widgetLayout->addWidget(insObjEdit, 5, 1);

            QLabel* areaLabel = new QLabel("House's area:");
            QLineEdit* areaEdit = new QLineEdit();
            widgetLayout->addWidget(areaLabel, 6, 0);
            widgetLayout->addWidget(areaEdit, 6, 1);

            QPushButton* submitButton = new QPushButton("Submit");
            widgetLayout->addWidget(submitButton, 7, 0);
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitHomeButton_clicked()));
            break;
        }
        case widgetStatus::find:{
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QLabel* nameLabel = new QLabel("Имя: ");
            QLineEdit* nameEdit = new QLineEdit();
            widgetLayout->addWidget(nameLabel, 0, 0);
            widgetLayout->addWidget(nameEdit, 0, 1);

            QLabel* surnameLabel = new QLabel("Фамилия: ");
            QLineEdit* surnameEdit = new QLineEdit();
            widgetLayout->addWidget(surnameLabel, 1, 0);
            widgetLayout->addWidget(surnameEdit, 1, 1);

            QLabel* dateLabel = new QLabel("Дата окончания: ");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 2, 0);
            widgetLayout->addWidget(dateEdit, 2, 1);

            QCheckBox* dateCheck = new QCheckBox("Искать по дате");
            widgetLayout->addWidget(dateCheck, 3, 0);

            QPushButton* submitButton = new QPushButton("Искать");
            widgetLayout->addWidget(submitButton, 4, 0);
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitFindButton_clicked()));
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

void MainWindow::on_addButton_clicked()
{
    changeWidget(widgetStatus::add);
}

void MainWindow::on_removeButton_clicked()
{
    int rowNum = table->currentRow();
    if(data.empty())
        return;
    if(tableData == nullptr)
    {
        data.removeAt(rowNum);
    }
    else
    {
        data.removeAt(tableData->at(rowNum));
        tableData->removeAt(rowNum);
    }
    drawTable();
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

void MainWindow::on_submitHomeButton_clicked(){
    QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
    QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
    QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
    QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
    QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
    QLineEdit* insObjEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());
    QLineEdit* areaEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(6, 1)->widget());

    if(idEdit     ->text() == "")
        return;
    if(nameEdit   ->text() == "")
        return;
    if(surnameEdit->text() == "")
        return;
    if(valueEdit  ->text() == "")
        return;
    if(insObjEdit ->text() == "")
        return;
    if(areaEdit   ->text() == "")
        return;

    if(editMode){
        int rowNum = table->currentRow();
        Insurance* item = data.at(rowNum);
        delete item;
        item = new HomeInsurance(idEdit->text().toInt(), nameEdit->text(),
                                 surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                 dateEdit->date(), insObjEdit->text(), areaEdit->text().toDouble());
        data.replace(rowNum, item);
        setEditMode(false);
    }
    else{
        Insurance* item = new HomeInsurance(idEdit->text().toInt(), nameEdit->text(),
                                            surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                            dateEdit->date(), insObjEdit->text(), areaEdit->text().toDouble());
        data.append(item);
    }
    drawTable();
    changeWidget(widgetStatus::hide);
}

void MainWindow::on_submitHealthButton_clicked(){
    QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
    QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
    QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
    QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
    QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
    QLineEdit* cityEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());

    if(idEdit     ->text() == "")
        return;
    if(nameEdit   ->text() == "")
        return;
    if(surnameEdit->text() == "")
        return;
    if(valueEdit  ->text() == "")
        return;
    if(cityEdit   ->text() == "")
        return;

    if(editMode){
        int rowNum = table->currentRow();
        Insurance* item = data.at(rowNum);
        delete item;
        item = new HealthInsurance(idEdit->text().toInt(), nameEdit->text(),
                                   surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                   dateEdit->date(), cityEdit->text());
        data.replace(rowNum, item);
        setEditMode(false);
    }
    else{
        Insurance* item = new HealthInsurance(idEdit->text().toInt(), nameEdit->text(),
                                              surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                              dateEdit->date(), cityEdit->text());
        data.append(item);
    }

    drawTable();
    changeWidget(widgetStatus::hide);
}

void MainWindow::on_submitCarButton_clicked(){
    QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
    QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
    QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
    QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
    QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
    QLineEdit* insObjEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());
    QLineEdit* carVINEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(6, 1)->widget());

    if(idEdit     ->text() == "")
        return;
    if(nameEdit   ->text() == "")
        return;
    if(surnameEdit->text() == "")
        return;
    if(valueEdit  ->text() == "")
        return;
    if(insObjEdit ->text() == "")
        return;
    if(carVINEdit ->text() == "")
        return;
    if(editMode){
        int rowNum = table->currentRow();
        Insurance* item = data.at(rowNum);
        delete item;
        item = new CarInsurance(idEdit->text().toInt(), nameEdit->text(),
                                surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                dateEdit->date(), insObjEdit->text(), carVINEdit->text().toInt());
        data.replace(rowNum, item);
        setEditMode(false);
    }
    else{
        Insurance* item = new CarInsurance(idEdit->text().toInt(), nameEdit->text(),
                                           surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                           dateEdit->date(), insObjEdit->text(), carVINEdit->text().toInt());
        data.append(item);
    }

    drawTable();
    changeWidget(widgetStatus::hide);
}

void MainWindow::on_findButton_clicked()
{
    changeWidget(widgetStatus::find);
}

void MainWindow::on_submitFindButton_clicked(){
    QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
    QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
    QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
    QCheckBox* dateCheck   = (QCheckBox*)(widgetLayout->itemAtPosition(3, 0)->widget());

    QString name = nameEdit->text();
    QString surname = surnameEdit->text();
    QDate date = dateEdit->date();
    bool searchDate = dateCheck->isChecked();

    if(name.length() == 0 && surname.length() == 0 && !searchDate){
        return;
    }

    tableData = new QVector<int>();
    for(int i = 0; i < data.length(); i++){
        bool checked = true;
        Insurance* currentItem = data.at(i);
        if(name.length() != 0 && currentItem->name != name){
            checked = false;
        }
        if(surname.length() != 0 && currentItem->surname != surname){
            checked = false;
        }
        if(searchDate && currentItem->endingDate != date){
            checked = false;
        }

        if(checked){
            tableData->append(i);
        }
    }

    table->setRowCount(tableData->length());
    for(int i = 0; i < tableData->length(); i++){
        setTableItem(data.at(tableData->at(i)), i);
    }
}

void MainWindow::on_discardButton_clicked()
{
    if(tableData != nullptr){
        delete tableData;
        tableData = nullptr;
    }



    drawTable();
    changeWidget(widgetStatus::hide);
}

void MainWindow::on_editButton_clicked()
{
    int row = table->currentRow();
    Insurance* item = data.at(row);
    QString id = item->getId();
    if(id[0] == "C"){
        CarInsurance* carItem = dynamic_cast<CarInsurance*>(item);
        changeWidget(widgetStatus::addCar);

        QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
        QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
        QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
        QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
        QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
        QLineEdit* insObjEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());
        QLineEdit* carVINEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(6, 1)->widget());

        idEdit      ->setText(QString::number(carItem->id));
        nameEdit    ->setText(carItem->name);
        surnameEdit ->setText(carItem->surname);
        valueEdit   ->setText(locale->toString(carItem->value));
        dateEdit    ->setDate(carItem->endingDate);
        insObjEdit  ->setText(carItem->insuranceObject);
        carVINEdit  ->setText(QString::number(carItem->carVIN));
    }
    else if(id[0] == "H"){
        HealthInsurance* healthItem = dynamic_cast<HealthInsurance*>(item);
        changeWidget(widgetStatus::addHealth);

        QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
        QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
        QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
        QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
        QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
        QLineEdit* cityEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());

        idEdit      -> setText(QString::number(healthItem->id));
        nameEdit    -> setText(healthItem->name);
        surnameEdit -> setText(healthItem->surname);
        valueEdit   -> setText(locale->toString(healthItem->value));
        dateEdit    -> setDate(healthItem->endingDate);
        cityEdit    -> setText(healthItem->insuranceCity);
    }
    else if(id[0] == "B"){
        HomeInsurance* homeItem = dynamic_cast<HomeInsurance*>(item);
        changeWidget(widgetStatus::addHome);

        QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
        QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
        QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
        QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
        QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
        QLineEdit* insObjEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());
        QLineEdit* areaEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(6, 1)->widget());

        idEdit      -> setText(QString::number(homeItem->id));
        nameEdit    -> setText(homeItem->name);
        surnameEdit -> setText(homeItem->surname);
        valueEdit   -> setText(locale->toString(homeItem->value));
        dateEdit    -> setDate(homeItem->endingDate);
        insObjEdit  -> setText(homeItem->insuranceObject);
        areaEdit    -> setText(QString::number(homeItem->homeArea));
    }
    setEditMode(true);
}

void MainWindow::setEditMode(bool state){
    if(state){
        table->setSelectionMode(QAbstractItemView::NoSelection);
        editMode = true;
    }
    else{
        table->setSelectionMode(QAbstractItemView::SingleSelection);
        editMode = false;
    }
}

void MainWindow::on_saveAction_triggered()
{
    if(!file.isOpen()){
        on_saveAtAction_triggered();
    }

    QDataStream stream(&file);

    for(auto i : data){
        QString id = i->getId();
        if(id[0] == "C"){
            CarInsurance* carItem = dynamic_cast<CarInsurance*>(i);
            stream<<"C"
                  <<carItem->id
                  <<carItem->name
                  <<carItem->surname
                  <<carItem->endingDate
                  <<carItem->value
                  <<carItem->insuranceObject
                  <<carItem->carVIN;

        }
        else if(id[0] == "H"){
            HealthInsurance* healthItem = dynamic_cast<HealthInsurance*>(i);
            stream<<"H"
                  <<healthItem->id
                  <<healthItem->name
                  <<healthItem->surname
                  <<healthItem->endingDate
                  <<healthItem->value
                  <<healthItem->insuranceCity;
        }
        else if(id[0] == "B"){
            HomeInsurance* homeItem = dynamic_cast<HomeInsurance*>(i);
            stream<<"B"
                  <<homeItem->id
                  <<homeItem->name
                  <<homeItem->surname
                  <<homeItem->endingDate
                  <<homeItem->value
                  <<homeItem->insuranceObject
                  <<homeItem->homeArea;
        }

    }
}

void MainWindow::on_saveAtAction_triggered()
{
    QStringList filters({"Data files (*.dat)"});

    QFileDialog dialog(this);
    dialog.setNameFilters(filters);
    dialog.setDirectory(QDir::home());
    if(file.isOpen()){
        file.close();
    }
    file.setFileName(dialog.getSaveFileName());
    file.open(QIODevice::ReadWrite);
    on_saveAction_triggered();
}

void MainWindow::on_openAction_triggered()
{

}
