#include "mainwindow.h"
#include<cmath>
#include<QMouseEvent>
#include<cstdlib>
#include <QPaintEvent>
#include<QPen>



mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
    //set window size
    setFixedSize(1280, 680);
    setUpdatesEnabled(true);

    //create close button
    close = new QPushButton("Close",this);
    close->setGeometry(10,640,100,30);
    close->show();
    connect(close, SIGNAL(clicked()), QApplication::instance(), SLOT (quit()));

    //create current algorithm name
    l =new QLabel("->Graph Solver<-",this);
    l->show();
    l->setGeometry(640,0,165,35);

    //create dikstra button
    Djikstrabutton = new QPushButton("Solve with Djikstra" ,this);
    Djikstrabutton->setGeometry(10,20,100,30);
    connect(Djikstrabutton,SIGNAL(clicked()),this,SLOT(SD()));

    //create bellman button
    QPushButton *Bellmanbutton=new QPushButton("Solve with Bellman",this);
    Bellmanbutton->setGeometry(10,70,100,30);
    connect(Bellmanbutton,SIGNAL(clicked()),this,SLOT(SB()));

    //create floyd button
    QPushButton *Floydbutton =new QPushButton("Solve with Floyd",this);
    Floydbutton->setGeometry(10,120,100,30);
    connect(Floydbutton,SIGNAL(clicked()),this,SLOT(SF()));

    //create reset button
    QPushButton *Resetbutton =new QPushButton("Reset all",this);
    Resetbutton->setGeometry(10,600,100,30);
    connect(Resetbutton,SIGNAL(clicked()),this,SLOT(Resetall()));
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
        //uncheck the button
        checkeditem->setChecked(false);
        checked=false;
        checkeditem=NULL;
    }
    else
    {
        if (event->button()==Qt::LeftButton)
        {
            //create a new button
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
     linepen.setWidth(1);
     QPoint p1,p2,p3,p4;


     linepen.setStyle( Qt::SolidLine );
     painter->setPen(linepen);
     for(int i=0;i<itemlist.size();i++)

     {
         for(int j=0;j<itemrelations[itemlist[i]].size();j++)

         {
             //draw the line
             painter->drawLine(* (itemrelations[itemlist[i]][j].line));

             //draw arrow

             //Arrowhead left
             if(itemrelations[itemlist[i]][j].line->x2()<itemrelations[itemlist[i]][j].item->x() )

             { p1.setX(itemrelations[itemlist[i]][j].item->x());
             p1.setY(itemrelations[itemlist[i]][j].item->y()+25);

             p2.setX(p1.x()-5); p2.setY(p1.y()-5);
             p3.setX(p1.x()-5); p3.setY(p1.y()+5);
             painter->drawLine(p2,p1);
             painter->drawLine(p1,p3);
             painter->drawLine(p2,p3); }


             //Arrowhead top

             if (itemrelations[itemlist[i]][j].line->y2()<itemrelations[itemlist[i]][j].item->y())
             {p1.setX(itemrelations[itemlist[i]][j].item->x()+25);
             p1.setY(itemrelations[itemlist[i]][j].item->y());

             p2.setX(p1.x()-5); p2.setY(p1.y()-5);
             p3.setX(p1.x()+5); p3.setY(p1.y()-5);
             painter->drawLine(p2,p1);
             painter->drawLine(p1,p3);
             painter->drawLine(p2,p3);}

             //Arrowhead bottom
            if ( itemrelations[itemlist[i]][j].line->y2()>itemrelations[itemlist[i]][j].item->y()+50 &&itemrelations[itemlist[i]][j].line->x2()<itemrelations[itemlist[i]][j].item->x()+50)

            {p1.setX(itemrelations[itemlist[i]][j].item->x()+25);
             p1.setY(itemrelations[itemlist[i]][j].item->y()+50);

             p2.setX(p1.x()-5); p2.setY(p1.y()+5);
             p3.setX(p1.x()+5); p3.setY(p1.y()+5);
             painter->drawLine(p2,p1);
             painter->drawLine(p1,p3);
             painter->drawLine(p2,p3);}


             //Arrowhead right
             if (itemrelations[itemlist[i]][j].line->x1()>itemrelations[itemlist[i]][j].item->x()+50 && itemrelations[itemlist[i]][j].line->y1()<itemrelations[itemlist[i]][j].item->y()+50)
             {p1.setX(itemrelations[itemlist[i]][j].item->x()+50);
             p1.setY(itemrelations[itemlist[i]][j].item->y()+25);

             p2.setX(p1.x()+5); p2.setY(p1.y()-5);
             p3.setX(p1.x()+5); p3.setY(p1.y()+5);
             painter->drawLine(p2,p1);
             painter->drawLine(p1,p3);
             painter->drawLine(p2,p3);}


             update();


         }


     }

        update();
        painter->end();
 }
















