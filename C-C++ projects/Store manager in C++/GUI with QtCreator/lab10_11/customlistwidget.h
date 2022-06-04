#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <Observer.h>
#include <Service.h>
#include <qlistview.h>



class CustomListModel: public QAbstractListModel
{
private:
    std::vector<Product> products;
public:
    CustomListModel(const vector<Product> products);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setProducts(const vector<Product>& products);
};

#endif // CUSTOMLISTWIDGET_H
