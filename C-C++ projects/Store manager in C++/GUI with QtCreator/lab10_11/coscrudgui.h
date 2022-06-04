#ifndef COSCRUDGUI_H
#define COSCRUDGUI_H

#include "customlistwidget.h"

#include <QWidget>
#include <Service.h>
#include <ShoppingCart.h>
#include <qlistwidget.h>
#include <qpushbutton.h>

class CosCRUDGUI : public QWidget, public Observer
{
private:
    Service& sv;
    CustomListModel* model;

    QListView* list = new QListView();
    QPushButton* btnEmpty = new QPushButton("Golire");
    QPushButton* btnGenerate = new QPushButton("Generare");

    void init();
    void con();
    void update();
public:
    CosCRUDGUI(Service& sv) : sv{sv} {
       init();
       con();
       update();
    };

signals:

};

#endif // COSCRUDGUI_H
