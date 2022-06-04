#ifndef DIALOGSORT_H
#define DIALOGSORT_H

#include <QString>
#include <qdialog.h>
#include <qradiobutton.h>


class dialogSort : public QDialog
{
private:
    QString choice;

    QRadioButton* radioName;
    QRadioButton* radioPrice;
    QRadioButton* radioTypeName;

    QPushButton* btnDone;
    QPushButton* btnCancel;

    void initializeGUIComponents();
    void connectSignalsSlots();
public:
    dialogSort();
    QString getChoice() const;
signals:

};
#endif
