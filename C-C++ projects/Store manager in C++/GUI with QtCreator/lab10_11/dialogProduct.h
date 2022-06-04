#ifndef DIALOGPRODUCT_H
#define DIALOGPRODUCT_H

#include "product.h"

#include <QDialog>
#include <QLineEdit>
#include <qlabel.h>

class dialogProduct : public QDialog
{
private:
    Product newProduct;

    QLabel* lblName;
    QLabel* lblType;
    QLabel* lblProducer;
    QLabel* lblPrice;

    QLineEdit* editName;
    QLineEdit* editType;
    QLineEdit* editProducer;
    QLineEdit* editPrice;

    QPushButton* btnDone;
    QPushButton* btnCancel;

    void initializeGUIComponents();
    void connectSignalsSlots();
public:
    dialogProduct();
    Product getNewProduct() const;
signals:

};

#endif // DIALOGPRODUCT_H
