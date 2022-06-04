#include "mainwindow.h"
#include "gui.h"
#include <QApplication>
#include "product.h"
#include "repository.h"
#include "console.h"
#include "service.h"
#include "myvector.h"
#include "ShoppingCart.h"
#include "ActiuneUndo.h"

void TestAll()
{
    TestProduct();
    TestRepository();
    TestService();
    TestVectorDinamic();
    TestShoppingCart();
    TestClassesUndo();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Repository repo;
    Service serv{repo};
    serv.AddSome();

    gui g{serv};
    //g.setWindowState(Qt::WindowMaximized);
    g.show();
    //TestAll();

    return a.exec();
}
