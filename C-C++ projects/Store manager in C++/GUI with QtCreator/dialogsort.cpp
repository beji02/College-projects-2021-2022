#include "dialogsort.h"

#include <QGroupBox>
#include <QRadioButton>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

dialogSort::dialogSort()
{
    initializeGUIComponents();
    connectSignalsSlots();
}
QString dialogSort::getChoice() const
{
    return this->choice;
}


void dialogSort::initializeGUIComponents()
{
    this->setFixedSize(200, 170);
    this->setWindowTitle("Sort");

    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    QGroupBox* radioBox = new QGroupBox;
    QVBoxLayout* radioBoxLayout = new  QVBoxLayout;
    radioBox->setLayout(radioBoxLayout);

    radioName = new QRadioButton(tr("Dupa nume"));
    radioPrice = new QRadioButton(tr("Dupa pret"));
    radioTypeName = new QRadioButton(tr("Dupa tip si nume"));

    radioName->setChecked(1);

    radioBoxLayout->addWidget(radioName);
    radioBoxLayout->addWidget(radioPrice);
    radioBoxLayout->addWidget(radioTypeName);


    QWidget* formButtons = new QWidget;
    QHBoxLayout* lyFormButtons = new QHBoxLayout;
    formButtons->setLayout(lyFormButtons);

    btnDone = new QPushButton("Done");
    btnCancel = new QPushButton("Cancel");

    lyFormButtons->addWidget(btnDone);
    lyFormButtons->addWidget(btnCancel);

    lyMain->addWidget(radioBox);
    lyMain->addWidget(formButtons);
}

void dialogSort::connectSignalsSlots()
{
    QObject::connect(btnDone, &QPushButton::clicked, [&]() {
        if(this->radioName->isChecked())
            this->choice = "Name";
        else if(this->radioPrice->isChecked())
            this->choice = "Price";
        else if(this->radioTypeName->isChecked())
            this->choice = "TypeName";
        this->accept();
    });
    QObject::connect(btnCancel, &QPushButton::clicked, [&]() {
        this->reject();
    });
}
