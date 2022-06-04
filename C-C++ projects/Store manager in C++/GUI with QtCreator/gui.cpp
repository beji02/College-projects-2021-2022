#include "gui.h"

#include <dialogFilter.h>
#include <dialogFind.h>
#include <dialogProduct.h>
#include <dialogSort.h>
#include <qboxlayout.h>
#include <qheaderview.h>
#include <QMessageBox>
#include <map>
#include <QDebug>
#include <CosCRUDGUI.h>
#include <CosReadOnlyGUI.h>


gui::gui(Service& Serv) : Serv{Serv}
{
    initializeGUIComponents();
    connectSignalsSlots();
    loadProductList(Serv.GetList());
}

void gui::initializeGUIComponents()
{
    this->setFixedSize(500, 600);
    this->setWindowTitle("Magazin");

    QVBoxLayout* lyMain = new QVBoxLayout;
    this->setLayout(lyMain);

    QWidget* left = new QWidget;
    QVBoxLayout* lyLeft = new QVBoxLayout;
    left->setLayout(lyLeft);

    QWidget* right = new QWidget;
    QVBoxLayout* lyRight = new QVBoxLayout;
    right->setLayout(lyRight);

    QWidget* right2 = new QWidget;
    this->lyRight2 = new QVBoxLayout;
    right2->setLayout(this->lyRight2);

    QWidget* top = new QWidget;
    QHBoxLayout* lyTop = new QHBoxLayout;
    top->setLayout(lyTop);

    QWidget* buttom = new QWidget;
    QHBoxLayout* lyButtom = new QHBoxLayout;
    buttom->setLayout(lyButtom);

    QWidget* buttomLeft = new QWidget;
    QVBoxLayout* lyButtomLeft = new QVBoxLayout;
    buttomLeft->setLayout(lyButtomLeft);

    QWidget* buttomRight = new QWidget;
    QVBoxLayout* lyButtomRight = new QVBoxLayout;
    buttomRight->setLayout(lyButtomRight);


    lbCartPrice = new QLabel("Cart price: 0");

    // setup table
    int noLines = 5;
    int noColumns = 5;
    this->tableProducts = new QTableWidget{noLines, noColumns};
    QStringList tblHeaderList;
    tblHeaderList << "ID" << "Nume" << "Tip" << "Pret" << "Producator";
    this->tableProducts->setHorizontalHeaderLabels(tblHeaderList);
    this->tableProducts->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->tableProducts->verticalHeader()->hide();

    // setup list for Cart
    this->listCart = new QListWidget();

    // setup buttons
    btnAddProduct = new QPushButton("Add product");
    btnDeleteProduct = new QPushButton("Delete product");
    btnModifyProduct = new QPushButton("Modify product");
    btnFindProduct = new QPushButton("Find product");
    btnFilterProducts = new QPushButton("Filter products");
    btnSortProducts = new QPushButton("Sort products");
    btnRefreshProducts = new QPushButton("Refresh list of products");

    btnGenerateCart = new QPushButton("Generate cart");
    btnAddToCart = new QPushButton("Add to cart");
    btnExportCart = new QPushButton("Export to file");
    btnEmptyCart = new QPushButton("Empty cart");

    btnUndo = new QPushButton("Undo");

    btnCosCrudGui = new QPushButton("Cos CRUD GUI");
    btnCosReadOnlyGui = new QPushButton("Cos read only GUI");

    ldCart = new QLineEdit();

    lyLeft->addWidget(tableProducts);
    lyLeft->addWidget(btnRefreshProducts);

    lyRight->addWidget(btnAddProduct);
    lyRight->addWidget(btnDeleteProduct);
    lyRight->addWidget(btnModifyProduct);
    lyRight->addWidget(btnFindProduct);
    lyRight->addWidget(btnFilterProducts);
    lyRight->addWidget(btnSortProducts);
    lyRight->addWidget(btnUndo); // to be implemented

    this->refreshButtonsType();

    lyTop->addWidget(left);
    lyTop->addWidget(right);
    lyTop->addWidget(right2);


    lyButtomLeft->addWidget(listCart);
    lyButtomLeft->addWidget(lbCartPrice);
    lyButtomRight->addWidget(btnGenerateCart);
    lyButtomRight->addWidget(btnAddToCart);
    lyButtomRight->addWidget(btnExportCart);
    lyButtomRight->addWidget(btnEmptyCart);
    lyButtomRight->addWidget(ldCart);

    lyButtomRight->addWidget(btnCosCrudGui);
    lyButtomRight->addWidget(btnCosReadOnlyGui);

    lyButtom->addWidget(buttomLeft);
    lyButtom->addWidget(buttomRight);

    lyMain->addWidget(top);
    lyMain->addWidget(buttom);
}

void gui::refreshButtonsType()
{
    QLayoutItem* item;
        while ( ( item = lyRight2->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }

    auto v = Serv.GetList();

    map<string, int> dictionar;
    for(auto el:v)
    {
        dictionar[el.GetType()] ++;
    }
    for(auto el:dictionar)
    {
        QPushButton* btn = new QPushButton(QString::fromStdString(el.first));
        QObject::connect(btn, &QPushButton::clicked, [&, el]() {
            QMessageBox::information(this, "Info", QString::number(el.second));
        });
        lyRight2->addWidget(btn);
    }
}

void gui::connectSignalsSlots()
{
    QObject::connect(btnAddProduct, &QPushButton::clicked, [&]() {
            dialogProduct d;
             d.setModal(true);
            if(d.exec() == QDialog::Accepted)
            {
                Product newProduct = d.getNewProduct();
                // do something with newProduct
                try
                {
                    Serv.Add(newProduct.GetName(), newProduct.GetType(), newProduct.GetProducer(), newProduct.GetPrice());
                    loadProductList(Serv.GetList());
                    //cout << "Produs adaugat cu succes!\n";
                    QMessageBox::information(this, "Info", QString::fromStdString("Produs adaugat cu succes!"));
                    refreshButtonsType();
                }
                catch(InvalidInput e)
                {
                    //cout << e.what();
                    QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
                }
            }
    });
    QObject::connect(btnDeleteProduct, &QPushButton::clicked, [&]() {
            if(tableProducts->selectedItems().empty())
            {
                QMessageBox::information(this, "Warning", QString::fromStdString("Selectati id-ul produsului inainte."));
                return;
            }
            int row = tableProducts->selectedRanges().constFirst().topRow();
            int id = tableProducts->item(row, 0)->text().toInt();

            try
            {
                Serv.Remove(id);
                loadProductList(this->Serv.GetList());
                QMessageBox::information(this, "Info", QString::fromStdString("Produs sters cu succes!"));
                refreshButtonsType();
            }
            catch (NoProductWithId e)
            {
                QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
            }
    });
    QObject::connect(btnModifyProduct, &QPushButton::clicked, [&]() {
            if(tableProducts->selectedItems().empty())
            {
                QMessageBox::information(this, "Warning", QString::fromStdString("Selectati id-ul produsului inainte."));
                return;
            }
            int row = tableProducts->selectedRanges().constFirst().topRow();
            int id = tableProducts->item(row, 0)->text().toInt();

            dialogProduct d;
            d.setModal(true);

            if(d.exec() == QDialog::Accepted)
            {
                Product newProduct = d.getNewProduct();

                // do something with newProduct
                try
                {
                    Serv.Update(id, newProduct.GetName(), newProduct.GetType(), newProduct.GetProducer(), newProduct.GetPrice());
                    loadProductList(Serv.GetList());
                    QMessageBox::information(this, "Info", QString::fromStdString("Produs modificat cu succes!"));
                    refreshButtonsType();
                }
                catch (NoProductWithId e)
                {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
                }
                catch (InvalidInput e)
                {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
                }
            }
    });
    QObject::connect(btnRefreshProducts, &QPushButton::clicked, [&]() {
            loadProductList(this->Serv.GetList());
    });
    QObject::connect(btnFindProduct, &QPushButton::clicked, [&]() {
            dialogFind d;
            d.setModal(true);
            if(d.exec() == QDialog::Accepted)
            {
                QString name = d.getName();
                // do something with name
                try
                {
                    Product product = Serv.Find(name.toStdString());
                    QMessageBox::information(this, "Info", QString::fromStdString("Exista " + product.GetName() + " la " + to_string(product.GetPrice()) + " lei."));
                }
                catch (InvalidInput e)
                {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
                }
                catch (NoProductWithName e)
                {
                    QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
                }
            }
    });
    QObject::connect(btnFilterProducts, &QPushButton::clicked, [&]() {
            dialogFilter d;
            d.setModal(true);
            if(d.exec() == QDialog::Accepted)
            {
                Choice choice = d.getChoice();
                VectorDinamic<Product> retList;
                // do something with choice
                if(choice.Type == "Name")
                    retList = Serv.FilterName(choice.Param.toStdString());
                else if(choice.Type == "Producer")
                    retList = Serv.FilterProducer(choice.Param.toStdString());
                else if(choice.Type == "Price")
                    retList = Serv.FilterPrice(choice.Param.toInt());
                else if(choice.Type == "Less")
                {
                    try
                    {
                        retList = Serv.FilterLess(choice.Param.toInt());
                    }
                    catch(NoProductWithPrice e)
                    {
                        QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
                        return;
                    }
                }
                loadProductList(retList);
            }
    });
    QObject::connect(btnSortProducts, &QPushButton::clicked, [&]() {
            dialogSort d;
            d.setModal(true);
            if(d.exec() == QDialog::Accepted)
            {
                QString choice = d.getChoice();
                // do something with choice
                if(choice == "Price")
                    Serv.SortList(1);
                else if(choice == "Name")
                    Serv.SortList(2);
                else if(choice == "TypeName")
                    Serv.SortList(3);
                loadProductList(Serv.GetList());
            }
    });
    QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
        try
        {
            Serv.Undo();
            loadProductList(Serv.GetList());
            refreshButtonsType();
        }
        catch(NoUndoOperation e)
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(btnGenerateCart, &QPushButton::clicked, [&]()
    {;
        if(ldCart->text().isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Add the number of products you want to generate.");
            return;
        }
        try
        {
            int nr_produse = ldCart->text().toInt();
            ldCart->clear();
            Serv.GenerateCart(nr_produse);
            const auto& price = Serv.Cart.GetTotal();
            QMessageBox::information(this, "Info", "Cos generat cu succes!");
            loadCart(Serv.Cart.GetAll(), price);
        }
        catch (EmptyList e)
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(btnAddToCart, &QPushButton::clicked, [&](){
        if(tableProducts->selectedItems().empty())
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString("Selectati numele produsului inainte."));
            return;
        }
        int row = tableProducts->selectedRanges().constFirst().topRow();
        string nume;
        nume = tableProducts->item(row, 1)->text().toStdString();

        try
        {
            Serv.Cart.Add(nume);
            QMessageBox::information(this, "Information", QString::fromStdString("Produs adaugat cu succes in cos!"));
            const auto& price = Serv.Cart.GetTotal();
            loadCart(Serv.Cart.GetAll(), price);
        }
        catch (NoProductWithName e)
        {
            QMessageBox::warning(this, "warning", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(btnExportCart, &QPushButton::clicked, [&](){
        if(ldCart->text().isEmpty())
        {
            QMessageBox::warning(this, "Warning", "Add file name for export.");
            return;
        }
        try
        {
            string nume_fisier = ldCart->text().toStdString();
            ldCart->clear();
            Serv.Cart.Export(nume_fisier);
            QMessageBox::information(this, "Information", QString::fromStdString("Cosul a fost exportat cu succes."));
        }
        catch (CorruptedFile e)
        {
            QMessageBox::warning(this, "Warning", QString::fromStdString(e.what()));
        }
    });
    QObject::connect(btnEmptyCart, &QPushButton::clicked, [&](){
        Serv.Cart.Empty();
        QMessageBox::information(this, "Information", QString::fromStdString("Cosul a fost golit cu succes."));
        const auto& price = Serv.Cart.GetTotal();
        loadCart(Serv.Cart.GetAll(), price);
    });
    QObject::connect(tableProducts, &QTableWidget::itemSelectionChanged, [&](){
        for(int i=0; i<this->tableProducts->rowCount(); i++)
        {
            //qDebug()<<this->tableProducts->rowCount()<<"\n";
            for(int j=0; j<this->tableProducts->columnCount(); j++)
            {
                //qDebug()<<this->tableProducts->columnCount()<<"\n";
                this->tableProducts->item(i, j)->setBackground(QBrush());
            }
        }
        if(tableProducts->selectedItems().empty())
            return;
        int row = tableProducts->selectedRanges().constFirst().topRow();
        for(int j=0; j<this->tableProducts->columnCount(); j++)
            tableProducts->item(row, j)->setBackground(Qt::green);
    });
    QObject::connect(btnCosCrudGui, &QPushButton::clicked, [&](){

        CosCRUDGUI* cos = new CosCRUDGUI(Serv);
        cos->show();
    });
    QObject::connect(btnCosReadOnlyGui, &QPushButton::clicked, [&](){
        CosReadOnlyGUI* cos = new CosReadOnlyGUI(Serv);
        cos->show();
    });

}

void gui::loadProductList(vector<Product> Products)
{
    this->listOfProducts = Products;
    this->tableProducts->clearContents();
    this->tableProducts->setRowCount(Products.size());

    int lineNumber = 0;
    for (auto& el : Products) {
        this->tableProducts->setItem(lineNumber, 0, new QTableWidgetItem(QString::number(el.GetId())));
        this->tableProducts->setItem(lineNumber, 1, new QTableWidgetItem(QString::fromStdString(el.GetName())));
        this->tableProducts->setItem(lineNumber, 2, new QTableWidgetItem(QString::fromStdString(el.GetType())));
        this->tableProducts->setItem(lineNumber, 3, new QTableWidgetItem(QString::number(el.GetPrice())));
        this->tableProducts->setItem(lineNumber, 4, new QTableWidgetItem(QString::fromStdString(el.GetProducer())));
        lineNumber++;
    }
    loadCart(this->Serv.Cart.GetAll(), this->Serv.Cart.GetTotal());
}

void gui::loadCart(vector<Product> Products, int price)
{
    this->listOfProductsCart = Products;

    int lineNumber = 0;
    this->listCart->clear();
    for (auto& el : Products) {
        this->listCart->addItem(new QListWidgetItem(QString::fromStdString(el.GetName())));
        lineNumber++;
    }
    this->lbCartPrice->setText("Cart price: " + QString::number(price));
}
