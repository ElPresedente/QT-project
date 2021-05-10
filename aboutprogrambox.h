#ifndef ABOUTPROGRAMBOX_H
#define ABOUTPROGRAMBOX_H

#include <QLabel>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>

class AboutProgramBox : public QDialog
{
    Q_OBJECT
private:
    QLabel* programDescripton;

    QLabel* githubLink;

    QLabel* licenceLabel;

    QBoxLayout* boxLayout;

    QPushButton* closeButton;

public:
    AboutProgramBox(QWidget *parent = nullptr);
};

#endif // ABOUTPROGRAMBOX_H
