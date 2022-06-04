#ifndef GUI_H
#define GUI_H

#include "service.h"
#include <QLabel>
#include <QListView>
#include <QListWidget>
#include <QPushButton>
#include <qboxlayout.h>
#include <qtablewidget.h>
#include <qwidget.h>
#include "product.h"



class gui : public QWidget
{
private:
    Service& Serv;
    vector<Product> listOfProducts;
    vector<Product> listOfProductsCart;

    QPushButton* btnAddProduct;
    QPushButton* btnDeleteProduct;
    QPushButton* btnModifyProduct;
    QPushButton* btnFindProduct;
    QPushButton* btnFilterProducts;
    QPushButton* btnSortProducts;
    QPushButton* btnRefreshProducts;

    QVBoxLayout* lyRight2;

    QTableWidget* tableProducts;
    QListWidget* listCart;

    QPushButton* btnGenerateCart;
    QPushButton* btnAddToCart;
    QPushButton* btnExportCart;
    QPushButton* btnEmptyCart;

    QPushButton* btnCosCrudGui;
    QPushButton* btnCosReadOnlyGui;

    QLineEdit* ldCart;
    QLabel* lbCartPrice;
    // undo pt functionalitatile fara cart
    QPushButton* btnUndo;


    void initializeGUIComponents();

    void connectSignalsSlots();
    void loadProductList(vector<Product> Products);
    void loadCart(vector<Product> Products, int price);
    void refreshButtonsType();
public:
    gui(Service& Serv);


signals:


};

#endif // GUI_H
