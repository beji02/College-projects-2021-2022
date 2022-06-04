#include "coscrudgui.h"

#include <QHBoxLayout>



void CosCRUDGUI::init()
{
    QHBoxLayout* mainLayout = new QHBoxLayout();

    QVBoxLayout* leftLayout = new QVBoxLayout();
    QVBoxLayout* rightLayout = new QVBoxLayout();

    leftLayout->addWidget(list);
    model = new CustomListModel{ sv.GetList() };
    list->setModel(model);

    rightLayout->addWidget(btnEmpty);
    rightLayout->addWidget(btnGenerate);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);
}

void CosCRUDGUI::con()
{
    sv.Cart.addObserver(this);
    QObject::connect(btnGenerate, &QPushButton::clicked, [&](){
        sv.GenerateCart(10);
    });
    QObject::connect(btnEmpty, &QPushButton::clicked, [&](){
        sv.Cart.Empty();
    });
}

void CosCRUDGUI::update()
{
    int lineNumber = 0;
    auto obiecte = sv.Cart.GetAll();
    model->setProducts(obiecte);
    /*
    list->clear();
    for (auto& el : obiecte) {
        this->list->addItem(new QListWidgetItem(QString::fromStdString(el.GetName())));
        lineNumber++;
    }
    */
}
