#ifndef COSREADONLYGUI_H
#define COSREADONLYGUI_H

#include <Observer.h>
#include <Service.h>
#include <qwidget.h>



class CosReadOnlyGUI: public QWidget, public Observer
{
private:
    Service& sv;
    void update() override;
    void paintEvent(QPaintEvent* ev) override;
public:
    CosReadOnlyGUI(Service& sv) : sv{sv} {
        sv.Cart.addObserver(this);
        update();
    };
};

#endif // COSREADONLYGUI_H
