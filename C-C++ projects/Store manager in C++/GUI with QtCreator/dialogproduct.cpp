#include "dialogproduct.h"

#include <QVBoxLayout>
#include <qformlayout.h>
#include <qpushbutton.h>


dialogProduct::dialogProduct()
{
    initializeGUIComponents();
    connectSignalsSlots();
}

void dialogProduct::initializeGUIComponents()
{
    this->setFixedSize(200, 200);
    this->setWindowTitle("Produs");

    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    QWidget* form = new QWidget;
    QFormLayout* lyForm = new QFormLayout;
    form->setLayout(lyForm);

    lblName = new QLabel("Name");
    lblType = new QLabel("Type");
    lblProducer = new QLabel("Producer");
    lblPrice = new QLabel("Price");

    editName = new QLineEdit;
    editType = new QLineEdit;
    editProducer = new QLineEdit;
    editPrice = new QLineEdit;

    lyForm->addRow(lblName, editName);
    lyForm->addRow(lblType, editType);
    lyForm->addRow(lblProducer, editProducer);
    lyForm->addRow(lblPrice, editPrice);

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

void dialogProduct::connectSignalsSlots()
{
    QObject::connect(btnDone, &QPushButton::clicked, [&]() {
        string name = editName->text().toStdString();
        string type = editType->text().toStdString();
        string producer = editProducer->text().toStdString();
        int price = editPrice->text().toInt();
        this->newProduct = Product(name, type, price, producer);
        this->accept();
    });
    QObject::connect(btnCancel, &QPushButton::clicked, [&]() {
        this->reject();
    });
}

Product dialogProduct::getNewProduct() const
{
    return this->newProduct;
}
