#include "mainwindow.h"
#include<cmath>
#include<QMouseEvent>
#include<cstdlib>
mainwindow::mainwindow(QWidget *parent) : QWidget(parent)
{
setFixedSize(800, 600);
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
            itemlist.insert(itemn,item);
            itemn++;
        }
    }
    return;

}
QLine MinimumSideDistance(Button *b1 , Button *b2)
{
   QLine line;
   int x,y,x1,x2,y1,y2,i,j,xs,ys;
   float min=10000;
   x1=b1->x();
   y1=b1->y();
   x2=b2->x();
   y2=b2->y();
   for(i=0;i<2;i++)
       for(j=0;j<2;j++)
       {
           x=x1-25-i*25+j*25;
           y=y1-50+j*25+i*25;
           for(int k=0;k<2;k++)
               for(int l=0;l<2;l++)
               {
                   xs=x2-25-k*25+l*25;
                   ys=y2-50+k*25+l*25;
                   if(min>sqrt(pow(xs-x,2)+pow(ys-y,2)))
                   {
                       min=sqrt(pow(xs-x,2)+pow(ys-y,2));
                       line.setLine(x,y,xs,ys);
                   }
               }


       }
   return line ;
}

 QLine* mainwindow::drawlink(Button* b1,Button* b2)
 {
     QLine* l=new QLine;
     *l=MinimumSideDistance(b1,b2);
     return l;
 }

