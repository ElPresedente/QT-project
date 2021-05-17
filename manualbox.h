#ifndef MANUALBOX_H
#define MANUALBOX_H

#include <QLabel>
#include <QDialog>
#include <QBoxLayout>
#include <QPushButton>
#include <QTextBrowser>

class ManualBox : public QDialog
{
    Q_OBJECT
private:

    QBoxLayout* boxLayout;

    QTextBrowser* html;

    QPushButton* closeButton;

public:
    ManualBox(QWidget* parent = nullptr);
};

#endif // MANUALBOX_H
