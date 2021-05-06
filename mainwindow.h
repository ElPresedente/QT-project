#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include <QWidget>
#include <QtWidgets>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QTableWidget>
#include <QGridLayout>
#include "carinsurance.h"
#include "healthinsurance.h"
#include "homeinsurance.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum widgetStatus{
    hide,
    add,
    addCar,
    addHome,
    addHealth
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_addButton_clicked();

    void on_removeButton_clicked();

    void on_carInsuranceButton_clicked();

    void on_healthInsuranceButton_clicked();

    void on_homeInsuranceButton_clicked();

    void test(int);

private:
    void drawTable();
    void setTableItem(Insurance* ptr, int rowNum);
    void changeWidget(widgetStatus);



    Ui::MainWindow *ui;
    QTableWidget* table;
    QList<Insurance*> data;

    QGridLayout* widgetLayout;
    widgetStatus currentStatus;
};
#endif // MAINWINDOW_H
