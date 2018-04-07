#include "mainwindow.h"
#include<cmath>
#include<QMouseEvent>
#include<cstdlib>
#include <QPaintEvent>
#include<QPen>



mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
setFixedSize(800, 600);
setUpdatesEnabled(true);
close = new QPushButton("Close",this);
close->setGeometry(10,560,80,30);
close->show();
connect(close, SIGNAL(clicked()), QApplication::instance(), SLOT (quit()));
}

bool mainwindow::getchecked()
{return checked ;}

Button* mainwindow::getcheckeditem()
{return checkeditem ;}

void mainwindow::setcheckeditem(Button* b)
{
    mainwindow::checkeditem=b;
}

void mainwindow::setifchecked(bool v)
{
    checked=v;
}

void mainwindow::mousePressEvent(QMouseEvent *event)
{
    if (checked==true)
    {
        //unchecking the button
        checkeditem->setChecked(false);
        checked=false;
        checkeditem=NULL;
    }
    else
    {
        if (event->button()==Qt::LeftButton)
        {
            //creating a new button
            char* itemn_str= new char[3];
            sprintf(itemn_str,"%d",itemn);
            Button *item = new Button (this) ;
            item->setText(itemn_str);
            item->setGeometry((event->x())-25, (event->y())- 25,50,50);
            item->show();
            itemlist.append(item);
            itemn++;
        }
    }
    repaint();
    return;

}

void mainwindow::paintEvent(QPaintEvent*  )
 {
    QPainter *painter = new QPainter(this);


     QPen linepen(Qt::darkGray);
     linepen.setWidth(3);



     linepen.setStyle( Qt::SolidLine );
     painter->setPen(linepen);
     for(int i=0;i<itemlist.size();i++)
     {for(int j=0;j<itemrelations[itemlist[i]].size();j++)

         {
             painter->drawLine(* (itemrelations[itemlist[i]][j].line));
         }


     }

        update();
        painter->end();
 }
















