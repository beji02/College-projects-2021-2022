#include "customlistwidget.h"



CustomListModel::CustomListModel(const vector<Product> products): products{products}
{

}

int CustomListModel::rowCount(const QModelIndex &parent) const
{
    return products.size();
}


QVariant CustomListModel::data(const QModelIndex & index, int role) const {
    qDebug() << "get row:" << index.row();
        if (role == Qt::DisplayRole) {
            //qDebug() << "get row:" << index.row();
            auto sp = products[index.row()].GetName();
            return QString::fromStdString(sp);
        }
        if (role == Qt::BackgroundRole) {
            if (products[index.row()].GetName() == "Castraveti") {
                return QColor(Qt::green);
            }
            if (products[index.row()].GetName() == "Rosi") {
                return QColor(Qt::red);
            }
            if (products[index.row()].GetName() == "Mere") {
                return QColor(Qt::yellow);
            }
            if (products[index.row()].GetName() == "Portocale") {
                return QColor(QColorConstants::Svg::orange);
            }
        }
    return QVariant{};
}


void CustomListModel::setProducts(const vector<Product>& products) {
        this->products = products;
        auto topLeft = createIndex(0,0);
        auto bottomR = createIndex(rowCount(), 0);
        emit dataChanged(topLeft, bottomR);
    }
