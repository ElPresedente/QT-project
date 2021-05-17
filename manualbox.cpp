#include "manualbox.h"
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QTextBrowser>

ManualBox::ManualBox(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint)
{
    QFile file(QDir::currentPath()+"/manual.htm");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
    QString str;
    str = stream.readAll();
    html = new QTextBrowser(this);
    html->setOpenExternalLinks(true);
    html->setHtml(str);

    closeButton = new QPushButton("Закрыть");

    boxLayout->insertWidget(0, html);
    boxLayout->insertWidget(1, closeButton);

    setLayout(boxLayout);
    connect(closeButton, SIGNAL(clicked()), SLOT(accept()));

    this->resize(1000, 1000);
}
