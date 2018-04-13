#include "button.h"
#include"mainwindow.h"
#include <QPainter>

QLine MinimumSideDistance(int x1,int y1,int x2,int y2)
{
    //function to be used later: it determines the minimum distance line connecting between the sides of the buttons
    QLine line;
    int x,y,i,j,xs,ys;
    float min=10000;

    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
        {
            x=x1+30+i*30-j*30;
            y=y1+55-j*30-i*30;

            for(int k=0;k<2;k++)
                for(int l=0;l<2;l++)
                {
                    xs=x2+30+k*30-l*30;
                    ys=y2+55-k*30-l*30;
                    if(min>sqrt(pow(xs-x,2)+pow(ys-y,2)))
                    {
                        min=sqrt(pow(xs-x,2)+pow(ys-y,2));
                        line.setLine(x-5,y,xs-5,ys);

                    }
                }


        }

    return line ;
}




Button::Button(QWidget* parent):QToolButton(parent)
{
    setCheckable(true);
}




void Button::mousePressEvent(QMouseEvent* event)
{
    mainwindow* parent=(mainwindow*)parentWidget();
    int i,j;

    if ((event->button()==Qt::RightButton))
    {
        //delete links from other buttons to this one
        for (i=0;i< parent->itemlist.size();i++)
            if (parent->itemlist[i]!=this)
            {
                bool x=true;
                QVector<relatedbutton> &v1=parent->itemrelations[parent->itemlist[i]];
                for(j=0;j<v1.size()&&x;j++)
                    x=v1[j].item!=this;
                if (!x)
                {
                    delete v1[j-1].label;
                    delete v1[j-1].line;
                    v1.remove(j-1);
                }
            }
        //delete links from this button to others
        QVector<relatedbutton> &v=parent->itemrelations[this];
        for (i=0;i<v.size();i++)
        {
            delete v[i].label;
            delete v[i].line;
        }
        //delete this button
        parent->itemrelations.remove(this);
        parent->itemlist.removeOne(this);
        delete this ;
    }
}




void Button::mouseMoveEvent(QMouseEvent* event)
{

    if ((event->type()==QEvent::MouseMove)&&(event->button()!=Qt::RightButton))
    {
        mainwindow* parent=(mainwindow*)parentWidget();
        int i,j;
        relatedbutton rb;
        QPoint p=parent->mapFromGlobal(QCursor::pos());


        //update the positions of the lines and labels connected to this button
        for ( i=0;i< parent->itemlist.size();i++)
            if (parent->itemlist[i]!=this)
            {
                bool x=true;
                QVector<relatedbutton> v1=parent->itemrelations[parent->itemlist[i]];
                for( j=0;j<v1.size()&&x;j++)
                    x=v1[j].item!=this;
                if (!x)
                {
                    rb=parent->itemrelations[parent->itemlist[i]][j-1];
                    *(rb.line)=MinimumSideDistance(parent->itemlist[i]->x(),parent->itemlist[i]->y(),p.x()-25,p.y()-25);
                    rb.label->setGeometry(rb.line->center().x(),rb.line->center().y() ,30,30);
                }
            }


        //update the positions of the lines and labels connecting this button to others
        for( i=0;(i<parent->itemrelations[this].size());i++)
        {
            rb=parent->itemrelations[this][i];
            *(rb.line)=MinimumSideDistance(rb.item->x(),rb.item->y(),p.x()-25,p.y()-25);
            rb.label->setGeometry(rb.line->center().x(),rb.line->center().y() ,30,30);
        }


        //update this button's position
        setGeometry(p.x()-25, p.y()-25,50,50);
        moveevent=true;
        update();

    }

}




void Button::mouseReleaseEvent(QMouseEvent* event)
{
    mainwindow* parent=(mainwindow*)parentWidget();
    if ((event->button()==Qt::LeftButton)&&(moveevent==false))
    {
        if (parent->getchecked()==false)
        {
            //check the clicked button
            nextCheckState();
            parent->setcheckeditem(this);
            parent->setifchecked(true);
            if (parent->algo!=none)
            {
                //check the source button
                parent->pathpair[0]=this;
                parent->l->setText("Solution with Djikstra's algorithm :\n  choose the destination vertex");
            }
        }
        else
        {
            //create a link ,add link to containers and uncheck buttons
            if (parent->getcheckeditem()==this)
            {
                //uncheck if already checked
                this->setChecked(false);
                parent->setifchecked(false);
                parent->setcheckeditem(NULL);
            }
            else {
                if (parent->algo!=none)
                {
                    //check the destination button
                    parent->pathpair[1]=this;
                    parent->loop.exit();
                    parent->getcheckeditem()->setChecked(false);
                    parent->setcheckeditem(NULL);
                    parent->setifchecked(false);
                }
                else
                {
                    bool t=true;
                    QVector<relatedbutton> v1=parent->itemrelations[parent->getcheckeditem()];
                    for( int j=0;j<v1.size()&&t;j++)
                        t=v1[j].item!=this;
                    if(t)
                    {//create line and determine positions
                        QLine* line=new QLine;
                        *line=MinimumSideDistance(parent->getcheckeditem()->x(),parent->getcheckeditem()->y(),x(),y());

                        //create label and temporary lineEdit
                        this->setChecked(true);
                        QLabel* label =new QLabel(parent);
                        QLineEdit* lineed =new QLineEdit(parent) ;
                        lineed->setGeometry(line->center().x(),line->center().y() ,30,30);
                        lineed->setFocus();
                        lineed->show();


                        //wait for the user input
                        connect(lineed,SIGNAL(textEdited(QString)),label,SLOT(setText(QString)) );
                        QEventLoop loop;
                        QObject::connect(lineed, SIGNAL(returnPressed()), &loop, SLOT(quit()));
                        loop.exec();


                        //delete lineEdit and show label instead
                        delete lineed ;
                        label->setGeometry(line->center().x() ,line->center().y(),30,30);
                        label->show();


                        //update data containers
                        relatedbutton rb;
                        rb.item=this;
                        rb.label=label;
                        rb.line=line;
                        parent->itemrelations[parent->getcheckeditem()].append(rb);
                    }


                    //reset checked states to default
                    this->setChecked(false);
                    parent->getcheckeditem()->setChecked(false);
                    parent->setcheckeditem(NULL);
                    parent->setifchecked(false);
                    return;
                }}


        }
    }

    moveevent=false;
}



