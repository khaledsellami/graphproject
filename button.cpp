  //-----------------------------------------//
 //work of Khaled Sellami and Ilyes Yahyaoui//
//-----------------------------------------//

#include "button.h"
#include"mainwindow.h"
#include <QPainter>

QLine MinimumSideDistance(int x1,int y1,int x2,int y2,int t)
{
    //function to be used later: it determines the minimum distance line connecting between the sides of the buttons
    QLine line;
    int x,y,i,j,xs,ys,h;
    float min=10000;
    if (t==-1)
        h=0;
    else
        h=5;

    for(i=0;i<2;i++)
        for(j=0;j<2;j++)
        {
            x=x1+25+i*(25+h)-j*(25+h);
            y=y1+50+h-j*(25+h)-i*(25+h);

            for(int k=0;k<2;k++)
                for(int l=0;l<2;l++)
                {
                    xs=x2+25+k*30-l*30;
                    ys=y2+55-k*30-l*30;
                    if(min>sqrt(pow(xs-x,2)+pow(ys-y,2)))
                    {
                        min=sqrt(pow(xs-x,2)+pow(ys-y,2));
                        line.setLine(x,y,xs,ys);

                    }
                }


        }

    return line ;
}



Button::Button(QWidget* parent):QToolButton(parent)
{
    setCheckable(true);
}




int Button::relationexists(Button* b)
{
    //determines if b has this button as a predecessor and return its position in relations table if yes
    mainwindow* parent=(mainwindow*)parentWidget();
    bool x=true;
    int j;
    QVector<relatedbutton> v1=parent->itemrelations[this];
    for( j=0;j<v1.size()&&x;j++)
        x=(v1[j].item!=b);
    if (x)
        return -1;
    else
        return j-1;
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
                j=parent->itemlist[i]->relationexists(this);
                if (j!=-1)
                {
                    int t=this->relationexists(parent->itemlist[i]);
                    rb=parent->itemrelations[parent->itemlist[i]][j];
                    *(rb.line)=MinimumSideDistance(parent->itemlist[i]->x(),parent->itemlist[i]->y(),p.x()-25,p.y()-25,t);
                    rb.label->setGeometry(rb.line->center().x(),rb.line->center().y() ,30,30);
                }
            }

        //update the positions of the lines and labels connecting this button to others
        for( i=0;(i<parent->itemrelations[this].size());i++)
        {
            rb=parent->itemrelations[this][i];
            int t=rb.item->relationexists(this),h=0;
            if (t!=-1)
                h=20;
            *(rb.line)=MinimumSideDistance(p.x()-25,p.y()-25,rb.item->x(),rb.item->y(),t);
            rb.label->setGeometry(rb.line->center().x()-h,rb.line->center().y()-h,30,30);
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
                parent->pathpair[0]->setStyleSheet("Background: #b30000");
                QString s;
                if (parent->algo==dijkstra)
                    s="Dijkstra";
                else
                {
                    if (parent->algo==bellman)
                        s="Bellman";
                    else
                        s="DAG";
                }
                parent->l->setText("Solution with "+s+"'s algorithm :\n  choose the destination vertex");
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
                if (parent->algo!=none)
                {
                    //uncheck the source button
                    parent->pathpair[0]->setStyleSheet("");
                    QString s;
                    if (parent->algo==dijkstra)
                        s="Dijkstra";
                    else
                    {
                        if (parent->algo==bellman)
                            s="Bellman";
                        else
                            s="DAG";
                    }
                    parent->l->setText("Solution with "+s+"'s algorithm :\n  choose the source vertex");
                }
            }
            else {
                if (parent->algo!=none)
                {
                    //check the destination button
                    parent->pathpair[1]=this;
                    parent->pathpair[1]->setStyleSheet("Background: #b30000");
                    parent->loop.exit();
                    parent->getcheckeditem()->setChecked(false);
                    parent->setcheckeditem(NULL);
                    parent->setifchecked(false);
                }
                else
                {
                    int j=parent->getcheckeditem()->relationexists(this);
                    if(j==-1)
                    {
                        //create line and determine positions
                        QLine* line=new QLine;
                        int t=this->relationexists(parent->getcheckeditem()),h=0;
                        if(t!=-1)
                        {
                            *(parent->itemrelations[this][t].line)=MinimumSideDistance(x(),y(),parent->getcheckeditem()->x(),parent->getcheckeditem()->y(),t);
                            h=20;
                        }
                        *line=MinimumSideDistance(parent->getcheckeditem()->x(),parent->getcheckeditem()->y(),x(),y(),t);
                        //create label and temporary lineEdit
                        this->setChecked(true);
                        bool* ok=new bool(false);
                        QLabel* label =new QLabel(parent);
                        QLineEdit* lineed =new QLineEdit(parent) ;
                        while((*ok)==false)
                        {
                            *ok=true;
                            lineed->setGeometry(line->center().x()-h,line->center().y()-h ,30,30);
                            lineed->setFocus();
                            lineed->grabMouse();
                            lineed->show();


                            //wait for the user input
                            connect(lineed,SIGNAL(textEdited(QString)),label,SLOT(setText(QString)) );
                            QEventLoop loop;
                            QObject::connect(lineed, SIGNAL(returnPressed()), &loop, SLOT(quit()));
                            loop.exec();
                            lineed->text().toFloat(ok);
                            if(*ok==false)
                            {
                                parent->l->setText("ERROR : write a float");
                                parent->l->setStyleSheet("color: red");
                            }
                        }

                        //delete lineEdit and show label instead
                        delete lineed ;
                        parent->l->setText("->Graph Solver<-");
                        parent->l->setStyleSheet("");
                        label->setGeometry(line->center().x()-h ,line->center().y()-h,30,30);
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
                }
            }
        }
    }

    moveevent=false;
}



