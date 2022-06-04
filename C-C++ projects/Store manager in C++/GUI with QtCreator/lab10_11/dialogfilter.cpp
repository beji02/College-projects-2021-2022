#include "dialogfilter.h"

#include <QGroupBox>
#include <QRadioButton>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qpushbutton.h>

dialogFilter::dialogFilter()
{
    initializeGUIComponents();
    connectSignalsSlots();
}
Choice dialogFilter::getChoice() const
{
    return this->choice;
}


void dialogFilter::initializeGUIComponents()
{
    this->setFixedSize(200, 200);
    this->setWindowTitle("Filter");

    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    QGroupBox* radioBox = new QGroupBox;
    QVBoxLayout* radioBoxLayout = new  QVBoxLayout;
    radioBox->setLayout(radioBoxLayout);

    radioName = new QRadioButton(tr("Dupa nume"));
    radioProducer = new QRadioButton(tr("Dupa producator"));
    radioPrice = new QRadioButton(tr("Dupa pret exact"));
    radioLess = new QRadioButton(tr("Dupa pret mai mic"));

    radioName->setChecked(1);

    radioBoxLayout->addWidget(radioName);
    radioBoxLayout->addWidget(radioProducer);
    radioBoxLayout->addWidget(radioPrice);
    radioBoxLayout->addWidget(radioLess);


    editParam = new QLineEdit();

    QWidget* formButtons = new QWidget;
    QHBoxLayout* lyFormButtons = new QHBoxLayout;
    formButtons->setLayout(lyFormButtons);

    btnDone = new QPushButton("Done");
    btnCancel = new QPushButton("Cancel");

    lyFormButtons->addWidget(btnDone);
    lyFormButtons->addWidget(btnCancel);

    lyMain->addWidget(radioBox);
    lyMain->addWidget(editParam);
    lyMain->addWidget(formButtons);
}

void dialogFilter::connectSignalsSlots()
{
    QObject::connect(btnDone, &QPushButton::clicked, [&]() {
        this->choice.Param = this->editParam->text();

        if(radioName->isChecked())
            this->choice.Type = "Name";
        else if(radioProducer->isChecked())
            this->choice.Type = "Producer";
        else if(radioPrice->isChecked())
            this->choice.Type = "Price";
        else if(radioLess->isChecked())
            this->choice.Type = "Less";

        this->accept();
    });
    QObject::connect(btnCancel, &QPushButton::clicked, [&]() {
        this->reject();
    });
}
