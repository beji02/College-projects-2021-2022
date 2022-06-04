#ifndef DIALOGFIND_H
#define DIALOGFIND_H

#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qstring.h>



class dialogFind : public QDialog
{
private:
    QString name;
    QLabel* lblName;

    QLineEdit* editName;

    QPushButton* btnDone;
    QPushButton* btnCancel;

    void initializeGUIComponents();
    void connectSignalsSlots();
public:
    dialogFind();
    QString getName() const;
signals:

};

#endif // DIALOGFIND_H
