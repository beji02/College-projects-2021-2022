#ifndef DIALOGFILTER_H
#define DIALOGFILTER_H

#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qradiobutton.h>

struct Choice{
    QString Type;
    QString Param;
};

class dialogFilter : public QDialog
{
private:
    Choice choice;

    QRadioButton* radioName;
    QRadioButton* radioProducer;
    QRadioButton* radioPrice;
    QRadioButton* radioLess;

    QPushButton* btnDone;
    QPushButton* btnCancel;

    QLineEdit* editParam;

    void initializeGUIComponents();
    void connectSignalsSlots();
public:
    dialogFilter();
    Choice getChoice() const;
signals:

};
#endif // DIALOGFILTER_H
