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
    addHealth,
    find
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

    void on_submitHomeButton_clicked();

    void on_submitHealthButton_clicked();

    void on_submitCarButton_clicked();

    void on_findButton_clicked();

    void on_submitFindButton_clicked();

    void on_discardButton_clicked();

    void on_editButton_clicked();

    void on_saveAction_triggered();

    void on_saveAtAction_triggered();

    void on_openAction_triggered();

private:
    void drawTable();
    void setTableItem(Insurance* ptr, int rowNum);
    void changeWidget(widgetStatus);
    void setEditMode(bool);

    Ui::MainWindow *ui;
    QTableWidget* table;
    QList<Insurance*> data;
    QLocale* locale;
    QVector<int>* tableData; // ИЗМЕНИТЬ НАЗВАНИЕ
    bool editMode;

    QFile file;

    QGridLayout* widgetLayout;
    widgetStatus currentStatus;
};
#endif // MAINWINDOW_H
