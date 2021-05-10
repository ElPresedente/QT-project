#include "aboutprogrambox.h"

AboutProgramBox::AboutProgramBox(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint)
{
    programDescripton = new QLabel("Информационно-поисковая система \"Страховая компания\"\n"
                                   "Программа предназначена для сохранения и управления данными о страховых договорах компании");

    githubLink = new QLabel("<a href='https://github.com/ElPresedente/QT-project'>GitHub link</a>");
    githubLink->setOpenExternalLinks(true);
    licenceLabel = new QLabel("Электронная почта: <a href=\"mailto:vova171002@mail.com\">vova171002@gmail.com</a><br>"
                              "Разработчик: Воропаев Владимир Геннадьевич<br>"
                              "Приложение свободно для копирования и использования");

    licenceLabel->setOpenExternalLinks(true);

    boxLayout = new QBoxLayout(QBoxLayout::TopToBottom);

    closeButton = new QPushButton("Закрыть");
    connect(closeButton, SIGNAL(clicked()), SLOT(accept()));

    boxLayout->insertWidget(0, programDescripton);
    boxLayout->insertWidget(1, githubLink);
    boxLayout->insertWidget(2, licenceLabel);
    boxLayout->insertWidget(3, closeButton);
    setLayout(boxLayout);
}

