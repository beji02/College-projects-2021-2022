#include "cosreadonlygui.h"

#include <QPaintEvent>
#include <QPainter>





void CosReadOnlyGUI::update()
{
    repaint();
}

void CosReadOnlyGUI::paintEvent(QPaintEvent *ev)
{
    auto list = sv.Cart.GetAll();
    map<string, int> mapa;
    for(auto el:list)
        mapa[el.GetName()] ++;

    int kPortocale = mapa["Portocale"];
    int kMere = mapa["Mere"];
    int kRosii = mapa["Rosi"];
    int kCastraveti = mapa["Castraveti"];
    int kRest = list.size()-kPortocale-kMere-kRosii-kCastraveti;

    QPainter p{this};
    //p.drawLine(0, 0, width(), height());

    srand(time(0));
    for(int i=0; i<kPortocale; i++)
    {
        int dx = 2.0/3*this->height();
        int dy = 2.0/3*this->width();
        int pozx = rand()%dx;
        int pozy = rand()%dy;

        int raza = 50+rand()%50;
        p.setBrush(QColor("Orange"));
        p.drawEllipse(pozx, pozy, raza*1.2, raza);
    }
    for(int i=0; i<kMere; i++)
    {
        int dx = 2.0/3*this->height();
        int dy = 2.0/3*this->width();
        int pozx = rand()%dx;
        int pozy = rand()%dy;

        int raza = 50+rand()%50;
        p.setBrush(QColor("Yellow"));
        p.drawEllipse(pozx, pozy, raza*1.2, raza);
    }
    for(int i=0; i<kRosii; i++)
    {
        int dx = 2.0/3*this->height();
        int dy = 2.0/3*this->width();
        int pozx = rand()%dx;
        int pozy = rand()%dy;

        int raza = 50+rand()%50;
        p.setBrush(QColor("Red"));
        p.drawEllipse(pozx, pozy, raza*1.2, raza);
    }
    for(int i=0; i<kCastraveti; i++)
    {
        int dx = 2.0/3*this->height();
        int dy = 2.0/3*this->width();
        int pozx = rand()%dx;
        int pozy = rand()%dy;

        int raza = 50+rand()%50;
        p.setBrush(QColor("Green"));
        p.drawEllipse(pozx, pozy, raza*4, raza*0.5);
    }
    for(int i=0; i<kRest; i++)
    {
        int dx = 2.0/3*this->height();
        int dy = 2.0/3*this->width();
        int pozx = rand()%dx;
        int pozy = rand()%dy;

        p.drawLine(pozx, pozy, pozx+100, pozy+100);
    }



}
