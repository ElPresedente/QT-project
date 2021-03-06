#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    table = ui->tableWidget;
    table->setColumnWidth(0, 175);
    table->setColumnWidth(2, 175);
    table->setColumnWidth(4, 200);
    table->setColumnWidth(5, 200);

    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    currentStatus = widgetStatus::hide;
    locale = new QLocale();
    tableData = nullptr;
    this->setFixedSize(this->size());
    setEditMode(false);

    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->pushButton_3->hide();
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

            QLabel* idLabel = new QLabel("?????????? ????????????????:");
            QLineEdit* idEdit = new QLineEdit();
            idEdit->setValidator(new QIntValidator(0, 99999));
            widgetLayout->addWidget(idLabel, 0, 0);
            widgetLayout->addWidget(idEdit, 0, 1);

            QLabel* nameLabel = new QLabel("?????? ??????????????????????:");
            QLineEdit* nameEdit = new QLineEdit();
            QRegExp nameExp(R"([??-??][??-??]{20})");
            nameEdit->setValidator(new QRegExpValidator(nameExp));
            widgetLayout->addWidget(nameLabel, 1, 0);
            widgetLayout->addWidget(nameEdit, 1, 1);

            QLabel* surnameLabel = new QLabel("?????????????? ??????????????????????:");
            QLineEdit* surnameEdit = new QLineEdit();
            surnameEdit->setValidator(new QRegExpValidator(nameExp));
            widgetLayout->addWidget(surnameLabel, 2, 0);
            widgetLayout->addWidget(surnameEdit, 2, 1);

            QLabel* valueLabel = new QLabel("?????????????????? ??????????:");
            QLineEdit* valueEdit = new QLineEdit();
            QDoubleValidator* validator = new QDoubleValidator(0, 999999, 2);
            valueEdit->setValidator(validator);
            qDebug()<<validator->locale();
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("???????? ?????????????????? ????????????????:");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 4, 0);
            widgetLayout->addWidget(dateEdit, 4, 1);

            QLabel* insObjLabel = new QLabel("?????????? ????????????????????:");
            QLineEdit* insObjEdit = new QLineEdit();
            QRegExp rx(R"([??-??]\d{3}[??-??]{2})");
            insObjEdit->setValidator(new QRegExpValidator(rx));
            widgetLayout->addWidget(insObjLabel, 5, 0);
            widgetLayout->addWidget(insObjEdit, 5, 1);

            QLabel* carVINLabel = new QLabel("VIN ?????????? ????????????????????:");
            QLineEdit* carVINEdit = new QLineEdit();
            QRegExp re(R"([0-9]{17})");
            carVINEdit->setValidator(new QRegExpValidator(re));
            widgetLayout->addWidget(carVINLabel, 6, 0);
            widgetLayout->addWidget(carVINEdit, 6, 1);

            QPushButton* submitButton = new QPushButton("??????????????????????");
            widgetLayout->addWidget(submitButton, 7, 0);
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitCarButton_clicked()));
            break;
        }
        case widgetStatus::addHealth:{//HealthInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceCity);
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QLabel* idLabel = new QLabel("?????????? ????????????????:");
            QLineEdit* idEdit = new QLineEdit();
            idEdit->setValidator(new QIntValidator(0, 99999));
            widgetLayout->addWidget(idLabel, 0, 0);
            widgetLayout->addWidget(idEdit, 0, 1);

            QLabel* nameLabel = new QLabel("?????? ??????????????????????:");
            QLineEdit* nameEdit = new QLineEdit();
            QRegExp nameExp(R"([??-??][??-??]{20})");
            nameEdit->setValidator(new QRegExpValidator(nameExp));
            widgetLayout->addWidget(nameLabel, 1, 0);
            widgetLayout->addWidget(nameEdit, 1, 1);

            QLabel* surnameLabel = new QLabel("?????????????? ??????????????????????:");
            QLineEdit* surnameEdit = new QLineEdit();
            surnameEdit->setValidator(new QRegExpValidator(nameExp));
            widgetLayout->addWidget(surnameLabel, 2, 0);
            widgetLayout->addWidget(surnameEdit, 2, 1);

            QLabel* valueLabel = new QLabel("?????????????????? ??????????:");
            QLineEdit* valueEdit = new QLineEdit();
            valueEdit->setValidator(new QDoubleValidator(0, 999999, 2));
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("???????? ?????????????????? ????????????????:");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 4, 0);
            widgetLayout->addWidget(dateEdit, 4, 1);
            qDebug()<<dateEdit->date().isNull();

            QLabel* insCityLabel = new QLabel("??????????:");
            QLineEdit* insCityEdit = new QLineEdit();
            widgetLayout->addWidget(insCityLabel, 5, 0);
            widgetLayout->addWidget(insCityEdit, 5, 1);

            QPushButton* submitButton = new QPushButton("??????????????????????");
            widgetLayout->addWidget(submitButton, 7, 0);
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitHealthButton_clicked()));
            break;
        }
        case widgetStatus::addHome:{//HomeInsurance(int Id, QString Name, QString Surname, double Value, QDate EndingDate, QString InsuranceObj, double HomeArea);
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QLabel* idLabel = new QLabel("?????????? ????????????????:");
            QLineEdit* idEdit = new QLineEdit();
            idEdit->setValidator(new QIntValidator(0, 99999));
            widgetLayout->addWidget(idLabel, 0, 0);
            widgetLayout->addWidget(idEdit, 0, 1);

            QLabel* nameLabel = new QLabel("?????? ??????????????????????:");
            QLineEdit* nameEdit = new QLineEdit();
            QRegExp nameExp(R"([??-??][??-??]{20})");
            nameEdit->setValidator(new QRegExpValidator(nameExp));
            widgetLayout->addWidget(nameLabel, 1, 0);
            widgetLayout->addWidget(nameEdit, 1, 1);

            QLabel* surnameLabel = new QLabel("?????????????? ??????????????????????:");
            QLineEdit* surnameEdit = new QLineEdit();
            surnameEdit->setValidator(new QRegExpValidator(nameExp));
            widgetLayout->addWidget(surnameLabel, 2, 0);
            widgetLayout->addWidget(surnameEdit, 2, 1);

            QLabel* valueLabel = new QLabel("?????????????????? ??????????:");
            QLineEdit* valueEdit = new QLineEdit();
            valueEdit->setValidator(new QDoubleValidator(0, 999999, 2));
            widgetLayout->addWidget(valueLabel, 3, 0);
            widgetLayout->addWidget(valueEdit, 3, 1);

            QLabel* dateLabel = new QLabel("???????? ?????????????????? ????????????????:");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 4, 0);
            widgetLayout->addWidget(dateEdit, 4, 1);

            QLabel* insObjLabel = new QLabel("?????????? ????????:");
            QLineEdit* insObjEdit = new QLineEdit();
            widgetLayout->addWidget(insObjLabel, 5, 0);
            widgetLayout->addWidget(insObjEdit, 5, 1);

            QLabel* areaLabel = new QLabel("?????????????? ????????:");
            QLineEdit* areaEdit = new QLineEdit();
            areaEdit->setValidator(new QIntValidator(0, 99999));
            widgetLayout->addWidget(areaLabel, 6, 0);
            widgetLayout->addWidget(areaEdit, 6, 1);

            QPushButton* submitButton = new QPushButton("??????????????????????");
            widgetLayout->addWidget(submitButton, 7, 0);
            connect(submitButton, SIGNAL(clicked()),
                    this, SLOT(on_submitHomeButton_clicked()));
            break;
        }
        case widgetStatus::find:{
            if(currentStatus != widgetStatus::hide)
                changeWidget(widgetStatus::hide);
            widgetLayout = new QGridLayout(ui->widget);

            QLabel* nameLabel = new QLabel("??????: ");
            QLineEdit* nameEdit = new QLineEdit();
            widgetLayout->addWidget(nameLabel, 0, 0);
            widgetLayout->addWidget(nameEdit, 0, 1);

            QLabel* surnameLabel = new QLabel("??????????????: ");
            QLineEdit* surnameEdit = new QLineEdit();
            widgetLayout->addWidget(surnameLabel, 1, 0);
            widgetLayout->addWidget(surnameEdit, 1, 1);

            QLabel* dateLabel = new QLabel("???????? ??????????????????: ");
            QDateEdit* dateEdit = new QDateEdit();
            widgetLayout->addWidget(dateLabel, 2, 0);
            widgetLayout->addWidget(dateEdit, 2, 1);

            QCheckBox* dateCheck = new QCheckBox("???????????? ???? ????????");
            widgetLayout->addWidget(dateCheck, 3, 0);

            QPushButton* submitButton = new QPushButton("????????????");
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
    isModified = true;
}

void MainWindow::on_pushButton_2_clicked()
{
    Insurance *newdata = new HealthInsurance(2, "Name", "Surname", 54.125, QDate(2002, 10, 17), "Orel");
    data.append(newdata);
    drawTable();
    isModified = true;
}

void MainWindow::on_pushButton_3_clicked()
{
    Insurance *newdata = new HomeInsurance(3, "??????????", "??????????????", 150.3, QDate(2006, 11, 7), "????????", 250.5);
    data.append(newdata);
    drawTable();
    isModified = true;
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
    isModified = true;
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
    bool checked = false;

    if(idEdit     ->text() == "")
        checked = true;
    if(nameEdit   ->text() == "")
        checked = true;
    if(surnameEdit->text() == "")
        checked = true;
    if(valueEdit  ->text() == "")
        checked = true;
    if(insObjEdit ->text() == "")
        checked = true;
    if(areaEdit   ->text() == "")
        checked = true;

    if(checked){
        QMessageBox::warning(this, "????????????", "???????????? ?????????????? ??????????????????????");
        return;
    }

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
    isModified = true;
}

void MainWindow::on_submitHealthButton_clicked(){
    QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
    QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
    QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
    QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
    QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
    QLineEdit* cityEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());
    bool checked = false;

    if(idEdit     ->text() == ""){
        qDebug()<<"idEdit false";
        checked = true;
    }
    if(nameEdit   ->text() == ""){
        qDebug()<<"nameEdit false";
        checked = true;
    }
    if(surnameEdit->text() == ""){
        qDebug()<<"surnameEdit false";
        checked = true;
    }
    if(valueEdit  ->text() == ""){
        qDebug()<<"value false";
        checked = true;
    }
    if(cityEdit   ->text() == ""){
        qDebug()<<"cityEdit false";
        checked = true;
    }

    if(checked){
        QMessageBox::warning(this, "????????????", "???????????? ?????????????? ??????????????????????");
        return;
    }

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
    isModified = true;
}

void MainWindow::on_submitCarButton_clicked(){
    QLineEdit* idEdit      = (QLineEdit*)(widgetLayout->itemAtPosition(0, 1)->widget());
    QLineEdit* nameEdit    = (QLineEdit*)(widgetLayout->itemAtPosition(1, 1)->widget());
    QLineEdit* surnameEdit = (QLineEdit*)(widgetLayout->itemAtPosition(2, 1)->widget());
    QLineEdit* valueEdit   = (QLineEdit*)(widgetLayout->itemAtPosition(3, 1)->widget());
    QDateEdit* dateEdit    = (QDateEdit*)(widgetLayout->itemAtPosition(4, 1)->widget());
    QLineEdit* insObjEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(5, 1)->widget());
    QLineEdit* carVINEdit  = (QLineEdit*)(widgetLayout->itemAtPosition(6, 1)->widget());
    bool checked = false;

    if(idEdit     ->text() == "")
        checked = true;
    if(nameEdit   ->text() == "")
        checked = true;
    if(surnameEdit->text() == "")
        checked = true;
    if(valueEdit  ->text() == "")
        checked = true;
    if(insObjEdit ->text().length() != 6 )
        checked = true;
    if(carVINEdit ->text().length() != 17 )
        checked = true;
    if(checked){
        QMessageBox::warning(this, "????????????", "???????????? ?????????????? ??????????????????????");
        return;
    }

    qDebug()<<carVINEdit->text()<<"   "<<carVINEdit->text().toLongLong();

    if(editMode){
        int rowNum = table->currentRow();
        Insurance* item = data.at(rowNum);
        delete item;
        item = new CarInsurance(idEdit->text().toInt(), nameEdit->text(),
                                surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                dateEdit->date(), insObjEdit->text(), carVINEdit->text().toLongLong());
        data.replace(rowNum, item);
        setEditMode(false);
    }
    else{
        Insurance* item = new CarInsurance(idEdit->text().toInt(), nameEdit->text(),
                                           surnameEdit->text(), locale->toDouble(valueEdit->text()),
                                           dateEdit->date(), insObjEdit->text(), carVINEdit->text().toLongLong());
        data.append(item);
    }

    drawTable();
    changeWidget(widgetStatus::hide);
    isModified = true;
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
        if(name.length() != 0 && currentItem->getFirstName() != name){
            checked = false;
        }
        if(surname.length() != 0 && currentItem->getLastName() != surname){
            checked = false;
        }
        if(searchDate && currentItem->getDate() != date){
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
    isModified = true;
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

        idEdit      ->setText(QString::number(carItem->getIdNumber()));
        nameEdit    ->setText(carItem->getFirstName());
        surnameEdit ->setText(carItem->getLastName());
        valueEdit   ->setText(locale->toString(carItem->getValueNumber()));
        dateEdit    ->setDate(carItem->getDate());
        insObjEdit  ->setText(carItem->getInsuranceData());
        carVINEdit  ->setText(QString::number(carItem->getCarVIN()));
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

        idEdit      -> setText(QString::number(healthItem->getIdNumber()));
        nameEdit    -> setText(healthItem->getFirstName());
        surnameEdit -> setText(healthItem->getLastName());
        valueEdit   -> setText(locale->toString(healthItem->getValueNumber()));
        dateEdit    -> setDate(healthItem->getDate());
        cityEdit    -> setText(healthItem->getInsuranceCity());
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

        idEdit      -> setText(QString::number(homeItem->getIdNumber()));
        nameEdit    -> setText(homeItem->getFirstName());
        surnameEdit -> setText(homeItem->getLastName());
        valueEdit   -> setText(locale->toString(homeItem->getValueNumber()));
        dateEdit    -> setDate(homeItem->getDate());
        insObjEdit  -> setText(homeItem->getInsuranceData());
        areaEdit    -> setText(QString::number(homeItem->getHomeArea()));
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
    if(filePath == ""){
        on_saveAtAction_triggered();
        return;
    }

    QFile file(filePath);
    file.open(QIODevice::ReadWrite);
    writeToFile(file);
    file.close();
}

void MainWindow::on_saveAtAction_triggered()
{
    QFile file;
    QString fileName = QFileDialog::getSaveFileName(this, "?????????????????? ??????...", QDir::homePath(), "Data files (*.dat)");
    if(fileName.length() == 0){
        return;
    }
    filePath = fileName;
    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite);
    writeToFile(file);
    file.close();
}

void MainWindow::writeToFile(QFile &file){
    QDataStream stream(&file);
    stream<<data.length();
    if(data.length() == 0){
        return;
    }

    for(auto iter = data.begin(); iter != data.end(); iter++){
        Insurance* i = iter;
        QString id = i->getId();
        if(id[0] == "C"){
            CarInsurance* carItem = dynamic_cast<CarInsurance*>(i);
            stream<<1
                  <<carItem->getIdNumber()
                  <<carItem->getFirstName()
                  <<carItem->getLastName()
                  <<carItem->getDate()
                  <<carItem->getValueNumber()
                  <<carItem->getInsuranceData()
                  <<carItem->getCarVIN();

        }
        else if(id[0] == "H"){
            HealthInsurance* healthItem = dynamic_cast<HealthInsurance*>(i);
            stream<<2
                  <<healthItem->getIdNumber()
                  <<healthItem->getFirstName()
                  <<healthItem->getLastName()
                  <<healthItem->getDate()
                  <<healthItem->getValueNumber()
                  <<healthItem->getInsuranceCity();
        }
        else if(id[0] == "B"){
            HomeInsurance* homeItem = dynamic_cast<HomeInsurance*>(i);
            stream<<3
                  <<homeItem->getIdNumber()
                  <<homeItem->getFirstName()
                  <<homeItem->getLastName()
                  <<homeItem->getDate()
                  <<homeItem->getValueNumber()
                  <<homeItem->getInsuranceData()
                  <<homeItem->getHomeArea();
        }
    }
    isModified = false;
}

void MainWindow::on_openAction_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "?????????????? ????????", QDir::homePath(), "Data files (*.dat)");
    if(fileName.length() == 0){
        return;
    }
    if(filePath == fileName){
        return;
    }
    filePath = fileName;
    if(data.length() != 0){
        qDebug()<<"cleaning list";
        data.clear();
        qDebug()<<data.length();
    }

    QFile file(fileName);
    file.open(QIODevice::ReadWrite);

    QDataStream stream(&file);
    int length;
    stream>>length;

    for(int i = 0; i < length; i++){
        int type;
        stream>>type;
        qDebug()<<"get "<<type<<" type";
        try{
            if(type == 1){
                int id;
                QString name;
                QString surname;
                QDate endingDate;
                double value;
                QString insuranceObject;
                long long carVIN;
                stream>>id>>name>>surname>>
                        endingDate>>value>>
                        insuranceObject>>carVIN;
                Insurance* item = new CarInsurance(id, name, surname, value, endingDate, insuranceObject, carVIN);
                data.append(item);
            }
            else if(type == 2){
                int id;
                QString name;
                QString surname;
                QDate endingDate;
                double value;
                QString insuranceCity;
                stream>>id>>name>>surname>>
                        endingDate>>value>>
                        insuranceCity;
                Insurance* item = new HealthInsurance(id, name, surname, value, endingDate, insuranceCity);
                data.append(item);
            }
            else if(type == 3){
                int id;
                QString name;
                QString surname;
                QDate endingDate;
                double value;
                QString insuranceObject;
                double homeArea;
                stream>>id>>name>>surname>>
                        endingDate>>value>>
                        insuranceObject>>homeArea;
                Insurance* item = new HomeInsurance(id, name, surname, value, endingDate, insuranceObject, homeArea);
                data.append(item);
            }
            qDebug()<<"On end: "<<stream.atEnd();
        }
        catch(QString str){
            qDebug()<<str<<" error";
        }

    }
    qDebug()<<"readed!"<<data.length();
    file.close();
    drawTable();
    isModified = false;
}

void MainWindow::on_newAction_triggered()
{
    QFile file;
    QString fileName = QFileDialog::getSaveFileName(this, "?????????????? ????????", QDir::homePath(), "Data files (*.dat)");
    if(fileName.length() == 0){
        return;
    }
    filePath = fileName;
    file.setFileName(fileName);
    file.open(QIODevice::ReadWrite);
    file.close();
}

void MainWindow::on_aboutProgAction_triggered()
{
    AboutProgramBox* window = new AboutProgramBox(this);
    window->exec();
}

void MainWindow::on_manualAction_triggered()
{
    ManualBox* window = new ManualBox(this);
    window->exec();
}

void MainWindow::on_tableWidget_itemSelectionChanged()
{
    bool isEnabled = table->currentRow() != -1;
    ui->editButton  ->setEnabled(isEnabled);
    ui->removeButton->setEnabled(isEnabled);
}

void MainWindow::on_exitAction_triggered()
{
    qDebug()<<"exiting...";
    if(isModified){
        QMessageBox::StandardButton ret;
        ret = QMessageBox::warning(this, "Insurances manager",
                                   "?????????????????? ???????????????????",
                                   QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        if (ret == QMessageBox::Save)
        {
            on_saveAction_triggered();
        }
        if (ret == QMessageBox::Cancel)
        {
            return;
        }

    }
    this->close();
}
