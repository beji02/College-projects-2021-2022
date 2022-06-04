#include "dialogfind.h"

#include <qboxlayout.h>
#include <qformlayout.h>
#include <qpushbutton.h>

dialogFind::dialogFind()
{
    initializeGUIComponents();
    connectSignalsSlots();
}


QString dialogFind::getName() const
{
    return this->name;
}


void dialogFind::initializeGUIComponents()
{
    this->setFixedSize(200, 120);
    this->setWindowTitle("Find");

    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);

    lblName = new QLabel("Name");

    editName = new QLineEdit;

    lyForm->addRow(lblName, editName);

    QWidget* formButtons = new QWidget;
    QHBoxLayout* lyFormButtons = new QHBoxLayout;
    formButtons->setLayout(lyFormButtons);

    btnDone = new QPushButton("Done");
    btnCancel = new QPushButton("Cancel");

    lyFormButtons->addWidget(btnDone);
    lyFormButtons->addWidget(btnCancel);

    lyMain->addWidget(form);
    lyMain->addWidget(formButtons);
}

void dialogFind::connectSignalsSlots()
{
    QObject::connect(btnDone, &QPushButton::clicked, [&]() {
        this->name = editName->text();
        this->accept();
    });
    QObject::connect(btnCancel, &QPushButton::clicked, [&]() {
        this->reject();
    });
}
